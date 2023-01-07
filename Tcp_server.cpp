#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include "Tcp_server.h"
#include "Manazer.h"

Manazer manazer;

//pthread_t klient;
pthread_t server;
pthread_mutex_t  mutex;
pthread_cond_t condServer;
pthread_cond_t condKlient;


typedef struct {
    char *buffer;
    int newsockfd;
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
} KD;

char* Tcp_server::citaj(char *buffer, int newsockfd) {
    bzero(buffer, 256);
    int n = read(newsockfd, buffer, 255);
    if (n < 0) {
        perror("Error reading from socket");
        //return 4;
    }
    printf("Here is the message: %s\n", buffer);

    return buffer;
}

void Tcp_server::zapis(char *buffer, int newsockfd) {
    const char *msg = "I got your message";
    printf("Please enter a message: ");
    bzero(buffer, 256);
    //fgets(buffer, 255, stdin);
    buffer = "Vykonal si tah, zvol si figurku";
    int n = write(newsockfd, buffer, strlen(buffer) + 1);
    if (n < 0) {
        perror("Error writing to socket");
        //return 5;
    }
}

static void *hrajKlient(void *args) {

    KD *klientData = (KD *) args;
    DATA *d = (DATA *) klientData->data;

    do {
        pthread_mutex_lock(d->mutex);
        while (d->aktualneId != 1) {
            printf("Klient caka na server\n");
            pthread_cond_wait(d->condKlient, d->mutex);
        }

        int idHraca = klientData->id;
        /*d->manazer.getHraci()[idHraca].vykonajTah(znak, idFig);
        d->manazer.skontrolujFigurky(idHraca);
        d->manazer.getHraciaPlocha().vykresliPlochu();*/
        printf("prehadzujem na server\n");
        /*d->aktualneId = d->manazer.getDalsiHrac(d->aktualneId, 2);
        pthread_cond_signal(d->condServer);
        pthread_mutex_unlock(d->mutex);*/

    } while (d->manazer.beziHra());

    pthread_exit(nullptr);
}

static void *hrajServer(void *args) {

    SD *serverData = (SD *) args;
    DATA *d = (DATA *) serverData->data;

    do {
        pthread_mutex_lock(d->mutex);
        while (d->aktualneId != 0) {
            printf("Server caka na klienta aby napisal 'h'\n");
            pthread_cond_wait(d->condServer, d->mutex);
        }
        pthread_mutex_unlock(d->mutex);

        pthread_mutex_lock(d->mutex);
        do {
            Tcp_server::citaj(d->buffer, d->newsockfd);
        } while (*d->buffer != 'h');
        char znak = *d->buffer;

        Tcp_server::zapis(d->buffer,d->newsockfd);
        d->aktualneId = d->manazer.getDalsiHrac(d->aktualneId, 2);
        printf("prehadzujem na klienta aby zadal figurku\n");

        pthread_mutex_unlock(d->mutex);

        pthread_mutex_lock(d->mutex);
        while (d->aktualneId != 0) {
            printf("Server caka na klienta aby zadal figurku\n");
            pthread_cond_wait(d->condServer, d->mutex);
        }
        pthread_mutex_unlock(d->mutex);

        pthread_mutex_lock(d->mutex);
        //printf("prehadzujem na klienta aby zadal figurku\n");
        printf("%s%c%s", "figurka buffer = ", *d->buffer, "\n");


        /*do {
            Tcp_server::citaj(d->buffer, d->newsockfd);
        } while (d->buffer[0] != '0' || d->buffer[0] != '1' || d->buffer[0] != '2' || d->buffer[0] != '3');
        int idFig = d->buffer[0];*/
        int idFig = 1;

        int idHraca = serverData->id;

        d->manazer.getHraci()[idHraca].vykonajTah(znak, idFig);
        d->manazer.skontrolujFigurky(idHraca);
        d->manazer.getHraciaPlocha().vykresliPlochu();

        d->aktualneId = d->manazer.getDalsiHrac(d->aktualneId, 2);
        printf("prehadzujem na klienta\n");
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

    /*Manazer manazer;

    //pthread_t klient;
    pthread_t server;
    pthread_mutex_t  mutex;
    pthread_cond_t condServer;
    pthread_cond_t condKlient;*/

    pthread_mutex_init(&mutex, nullptr);
    pthread_cond_init(&condServer, nullptr);
    pthread_cond_init(&condKlient, nullptr);


    DATA data = {
            buffer, newsockfd, manazer, 0, &mutex, &condServer, &condKlient
    };
    SD serverData = {
            0, &data
    };
    /*KD klientData = {
            1, &data
    };*/

    //pthread_create(&klient, nullptr, hrajKlient, &klientData);
    pthread_create(&server, nullptr, hrajServer, &serverData);

    //pthread_join(klient, nullptr);
    pthread_join(server, nullptr);


    while (true) {


        bzero(buffer, 256);
        n = read(newsockfd, buffer, 255);
        if (n < 0) {
            perror("Error reading from socket");
            return 4;
        }
        printf("Here is the message: %s\n", buffer);

        const char *msg = "I got your message";
        printf("Please enter a message: ");
        bzero(buffer, 256);
        fgets(buffer, 255, stdin);
        n = write(newsockfd, buffer, strlen(buffer) + 1);
        if (n < 0) {
            perror("Error writing to socket");
            return 5;
        }


    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&condServer);
    //pthread_cond_destroy(&condKlient);

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



