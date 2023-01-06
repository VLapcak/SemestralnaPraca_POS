#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include "pthread.h"
#include "ZdielaneData.h"

static void *hrajKlient(void *args) {

    /*ZdielaneData::KD *klientData = (ZdielaneData::KD *) args;
    ZdielaneData::DATA *d = (ZdielaneData::DATA *) klientData->data;*/
    ZdielaneData::DATA *d = (ZdielaneData::DATA *) args;

    /*KD *klientData = (KD *) args;
    DATA *d = (DATA *) klientData->data;*/

    do {

        pthread_mutex_lock(d->mutex);
        while (d->aktualneId != 1) {
            printf("Klient caka na server\n");
            pthread_cond_wait(d->condKlient, d->mutex);
        }
        //int id = klientData->id;
        int id = d->idKlient;
        d->manazer.getHraci()[id].vykonajTah();
        d->manazer.skontrolujFigurky(id);
        d->manazer.getHraciaPlocha().vykresliPlochu();
        printf("prehadzujem na server\n");
        d->aktualneId = d->manazer.getDalsiHrac(d->aktualneId, 2);
        pthread_cond_signal(d->condServer);
        pthread_mutex_unlock(d->mutex);



    } while (d->manazer.beziHra());

    pthread_exit(nullptr);
}

int main(int argc, char **argv) {
    if (argc < 4) {
        perror("Klienta je nutne spustit s nasledujucimi argumentmi: adresa port pouzivatel.");
    }

    //ziskanie adresy a portu servera <netdb.h>
    struct hostent *server = gethostbyname(argv[1]);
    if (server == NULL) {
        perror("Server neexistuje.");
    }
    int port = atoi(argv[2]);
    if (port <= 0) {
        perror("Port musi byt cele cislo vacsie ako 0.");
    }
    char *userName = argv[3];

    //vytvorenie socketu <sys/socket.h>
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Chyba - socket.");
    }

    //definovanie adresy servera <arpa/inet.h>
    struct sockaddr_in serverAddress;
    bzero((char *) &serverAddress, sizeof (serverAddress));
    serverAddress.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *) &serverAddress.sin_addr.s_addr, server->h_length);
    serverAddress.sin_port = htons(port);

    if (connect(sock, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
        perror("Chyba - connect.");
    }

    //inicializacia dat zdielanych medzi vlaknami
    ZdielaneData zdielaneData;
    ZdielaneData::DATA data;
    zdielaneData.dataInit(&data, userName, sock);
    /*DATA data;
    data_init(&data, userName, sock);*/

    //vytvorenie vlakna pre zapisovanie dat do socketu <pthread.h>
    pthread_t thread;
    pthread_create(&thread, nullptr, hrajKlient, &data);

    //v hlavnom vlakne sa bude vykonavat citanie dat zo socketu
    //data_readData((void *) &data);

    //pockame na skoncenie zapisovacieho vlakna <pthread.h>
    pthread_join(thread, nullptr);
    //data_destroy(&data);

    //uzavretie socketu <unistd.h>
    close(sock);

    return (EXIT_SUCCESS);











    /*int sockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];

    if (argc < 3) {
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        return 1;
    }

    server = gethostbyname(argv[1]);
    if (server == nullptr) {
        fprintf(stderr, "Error, no such host\n");
        return 2;
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy(
            (char *) server->h_addr,
            (char *) &serv_addr.sin_addr.s_addr,
            server->h_length
    );
    serv_addr.sin_port = htons(atoi(argv[2]));

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        return 3;
    }

    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("Error connecting to socket");
        return 4;
    }

    int i = 0;
    while (i < 5) {
        i++;
        printf("Please enter a message: ");
        bzero(buffer, 256);
        fgets(buffer, 255, stdin);

        n = write(sockfd, buffer, strlen(buffer));
        if (n < 0) {
            perror("Error writing to socket");
            return 5;
        }

        bzero(buffer, 256);
        n = read(sockfd, buffer, 255);
        if (n < 0) {
            perror("Error reading from socket");
            return 6;
        }

        printf("%s\n", buffer);
    }
    close(sockfd);

    return 0;*/
}
