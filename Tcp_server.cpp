#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <netdb.h>
#include "Tcp_server.h"
#include "Manazer.h"
#include "ZdielaneData.h"

/*typedef struct {
    Manazer manazer;
    int aktualneId;
    pthread_mutex_t *mutex;
    pthread_cond_t *condServer;
    pthread_cond_t *condKlient;
} DATA;
typedef struct {
    int id;
    DATA *data;
} SD;
typedef struct {
    int id;
    DATA *data;
} KD;*/

/*static void *hrajKlient(void *args) {

    KD *klientData = (KD *) args;
    //KD *klientData = static_cast<KD *>(args);
    DATA *d = (DATA *) klientData->data;

    do {

        pthread_mutex_lock(d->mutex);
        while (d->aktualneId != 1) {
            printf("Klient caka na server\n");
            pthread_cond_wait(d->condKlient, d->mutex);
        }
        int id = klientData->id;
        d->manazer.getHraci()[id].vykonajTah();
        d->manazer.skontrolujFigurky(id);
        d->manazer.getHraciaPlocha().vykresliPlochu();
        printf("prehadzujem na server\n");
        d->aktualneId = d->manazer.getDalsiHrac(d->aktualneId, 2);
        pthread_cond_signal(d->condServer);
        pthread_mutex_unlock(d->mutex);



    } while (d->manazer.beziHra());

    pthread_exit(nullptr);
}*/

static void *hrajServer(void *args) {

    //ZdielaneData::SD *serverData = (ZdielaneData::SD *) args;
    //ZdielaneData::DATA *d = (ZdielaneData::DATA *) serverData->data;
    ZdielaneData::DATA *d = (ZdielaneData::DATA *) args;

    /*SD *serverData = (SD *) args;
    DATA *d = (DATA *) serverData->data;*/

    do {
        pthread_mutex_lock(d->mutex);
        while (d->aktualneId != 0) {
            printf("Server caka na klienta\n");
            pthread_cond_wait(d->condServer, d->mutex);
        }
        //int id = serverData->id;
        int id = d->idServer;
        d->manazer.getHraci()[id].vykonajTah();
        d->manazer.skontrolujFigurky(id);
        d->manazer.getHraciaPlocha().vykresliPlochu();
        printf("prehadzujem na klienta\n");
        d->aktualneId = d->manazer.getDalsiHrac(d->aktualneId, 2);
        pthread_cond_signal(d->condKlient);
        pthread_mutex_unlock(d->mutex);

    } while (d->manazer.beziHra());

    pthread_exit(nullptr);
}

int Tcp_server::create_server(int argc, char **argv) {

    if (argc < 3) {
        perror("Server je nutne spustit s nasledujucimi argumentmi: port pouzivatel.");
    }
    int port = atoi(argv[1]);
    if (port <= 0) {
        perror("Port musi byt cele cislo vacsie ako 0.");
    }
    char *userName = argv[2];

    //vytvorenie TCP socketu <sys/socket.h>
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        perror("Chyba - socket.");
    }

    //definovanie adresy servera <arpa/inet.h>
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;             //internetove sockety
    serverAddress.sin_addr.s_addr = INADDR_ANY;     //prijimanie spojenia z celeho internetu
    serverAddress.sin_port = htons(port);   //nastavenie portu

    //prepojenie adresy servera so socketom <sys/socket.h>
    if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
        perror("Chyba - bind.");
    }

    //server bude prijimat nove spojenia cez socket serverSocket <sys/socket.h>
    listen(serverSocket, 10);

    //server caka na pripojenie klienta <sys/socket.h>
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLength = sizeof(clientAddress);
    int clientSocket = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientAddressLength);

    //uzavretie pasivneho socketu <unistd.h>
    close(serverSocket);
    if (clientSocket < 0) {
        perror("Chyba - accept.");
    }

    //inicializacia dat zdielanych medzi vlaknami
    ZdielaneData zdielaneData;
    //ZdielaneData::SD data;
    ZdielaneData::DATA data;
    zdielaneData.dataInit(&data, userName, clientSocket);
    /*DATA data;
    data_init(&data, userName, clientSocket);*/

    //vytvorenie vlakna pre zapisovanie dat do socketu <pthread.h>
    pthread_t thread;
    pthread_create(&thread, NULL, hrajServer, &data);

    //v hlavnom vlakne sa bude vykonavat citanie dat zo socketu
    //data_readData((void *) &data);

    //pockame na skoncenie zapisovacieho vlakna <pthread.h>
    pthread_join(thread, NULL);
    //data_destroy(&data);

    //uzavretie socketu <unistd.h>
    close(clientSocket);

    return (EXIT_SUCCESS);






















    /*int sockfd, newsockfd;
    socklen_t cli_len;
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    char buffer[256];

    if (argc < 2) {
        fprintf(stderr, "usage %s port\n", argv[0]);
        return 1;
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(atoi(argv[1]));

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        return 1;
    }

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("Error binding socket address");
        return 2;
    }

    listen(sockfd, 5);
    cli_len = sizeof(cli_addr);

    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &cli_len);
    if (newsockfd < 0) {
        perror("ERROR on accept");
        return 3;
    }

    //spustam hru
    //Manazer *manazer = new Manazer();
    Manazer manazer;

    pthread_t klient;
    pthread_t server;
    *//*pthread_mutex_t  mutex;
    pthread_cond_t condServer;
    pthread_cond_t condKlient;



    pthread_mutex_init(&mutex, nullptr);
    pthread_cond_init(&condServer, nullptr);
    pthread_cond_init(&condKlient, nullptr);*//*

    *//*DATA data = {
            manazer,0, &mutex, &condServer, &condKlient
    };
    SD serverData = {
            0, &data
    };
    KD klientData = {
            1, &data
    };*//*


    ZdielaneData zdielaneData;
    ZdielaneData::DATA d;

    d.manazer = Manazer();
    zdielaneData.dataInit(&d);


    pthread_create(&klient, nullptr, hrajKlient, &klientData);
    pthread_create(&server, nullptr, hrajServer, &serverData);

    pthread_join(klient, nullptr);
    pthread_join(server, nullptr);


    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&condServer);
    pthread_cond_destroy(&condKlient);


    while (true) {


        bzero(buffer, 256);
        n = read(newsockfd, buffer, 255);
        if (n < 0) {
            perror("Error reading from socket");
            return 4;
        }
        //printf("Here is the message: %s\n", buffer);

        //const char *msg = "I got your message";
        printf("Please enter a message: ");
        bzero(buffer, 256);
        fgets(buffer, 255, stdin);
        n = write(newsockfd, buffer, strlen(buffer) + 1);
        if (n < 0) {
            perror("Error writing to socket");
            return 5;
        }


    }

    close(newsockfd);
    close(sockfd);

    return 0;*/
}

Tcp_server::Tcp_server(int argc, char **argv) {
    create_server(argc, argv);
}

void *Tcp_server::hrajHru(void *args) {
    return nullptr;
}

