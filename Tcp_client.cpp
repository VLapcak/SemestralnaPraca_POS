#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include "pthread.h"
#include "ZdielaneData.h"

int soketServera;

static void* hrajKlient(void *args) {

    data *d = (data *) args;
    data *buffer;
    pthread_mutex_lock(d->mutex);
    do {
        pthread_mutex_unlock(d->mutex);

        pthread_mutex_lock(d->mutex);
        recv(soketServera, &buffer, sizeof(&buffer), 0);
        pthread_mutex_unlock(d->mutex);

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
        send(soketServera, &d, sizeof(&d), 0);
        pthread_mutex_unlock(d->mutex);

        pthread_mutex_lock(d->mutex);
    } while (d->manazer.beziHra());
    pthread_mutex_unlock(d->mutex);

    pthread_exit(nullptr);
}


int main(int argc, char **argv) {
    if (argc < 4) {
        perror("Klienta je nutne spustit s nasledujucimi argumentmi: adresa port pouzivatel.");
    }

    //ziskanie adresy a portu servera <netdb.h>
    struct hostent *server = gethostbyname(argv[1]);
    if (server == nullptr) {
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

    soketServera = sock;
    //inicializacia dat zdielanych medzi vlaknami
    data d{};
    recv(sock, &d, sizeof(struct data), 0);
    //d.manazer.getHraciaPlocha().vykresliPlochu();

    //vytvorenie vlakna pre zapisovanie dat do socketu <pthread.h>
    pthread_t thread;
    pthread_create(&thread, nullptr, hrajKlient, &d);

    //pockame na skoncenie zapisovacieho vlakna <pthread.h>
    pthread_join(thread, nullptr);
    //data_destroy(&data);

    //uzavretie socketu <unistd.h>
    close(sock);

    return (EXIT_SUCCESS);

}

