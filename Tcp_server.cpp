#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include "Tcp_server.h"
#include "Manazer.h"

typedef struct {
    Manazer manazer;
    int aktualneId;
    int idServer;
    int idKlient;
    pthread_mutex_t *mutex;
    pthread_cond_t *condServer;
    pthread_cond_t *condKlient;
} DATA;

static void *hrajKlient(void *args) {

    DATA *d = (DATA *) args;

    do {
        pthread_mutex_lock(d->mutex);
        while (d->aktualneId != 1) {
            printf("Klient caka na server\n");
            pthread_cond_wait(d->condKlient, d->mutex);
        }
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

static void *hrajServer(void *args) {

    DATA *d = (DATA *) args;

    do {
        pthread_mutex_lock(d->mutex);
        while (d->aktualneId != 0) {
            printf("Server caka na klienta\n");
            pthread_cond_wait(d->condServer, d->mutex);
        }
        int id = d->idServer;
        //int id = d->idServer;
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

    int sockfd, newsockfd;
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

    Manazer manazer;
    int aktualneId = 0;
    const int idServer = 0;
    const int idKlient = 1;

    pthread_t klient;
    pthread_t server;
    pthread_mutex_t  mutex;
    pthread_cond_t condServer;
    pthread_cond_t condKlient;

    pthread_mutex_init(&mutex, nullptr);
    pthread_cond_init(&condServer, nullptr);
    pthread_cond_init(&condKlient, nullptr);

    DATA data = {
            manazer,aktualneId, idServer, idKlient, &mutex, &condServer, &condKlient
    };

    /*pthread_create(&klient, nullptr, hrajKlient, &data);
    pthread_create(&server, nullptr, hrajServer, &data);

    pthread_join(klient, nullptr);
    pthread_join(server, nullptr);


    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&condServer);
    pthread_cond_destroy(&condKlient);*/


    while (true) {


        bzero(buffer, 256);
        n = read(newsockfd, &data, 255);

        data.manazer.getHraciaPlocha().vykresliPlochu();
        printf("Server zadaj spravu: ");
        int id = data.manazer.getHraci()[data.aktualneId].vykonajTah();
        data.manazer.skontrolujFigurky(id);
        data.manazer.getHraciaPlocha().vykresliPlochu();
        //printf("prehadzujem na klienta\n");
        data.aktualneId = data.manazer.getDalsiHrac(data.aktualneId, 2);

        //n = read(newsockfd, buffer, 255);
        if (n < 0) {
            perror("Error reading from socket");
            return 4;
        }
        //printf("Here is the message: %s\n", buffer);

        //const char *msg = "I got your message";

        /*bzero(buffer, 256);
        fgets(buffer, 255, stdin);*/
        n = write(newsockfd, &data, sizeof(DATA));
        //n = write(newsockfd, buffer, strlen(buffer) + 1);
        if (n < 0) {
            perror("Error writing to socket");
            return 5;
        }


    }

    close(newsockfd);
    close(sockfd);

    return 0;
}

Tcp_server::Tcp_server(int argc, char **argv) {
    create_server(argc, argv);
}

void *Tcp_server::hrajHru(void *args) {
    return nullptr;
}

