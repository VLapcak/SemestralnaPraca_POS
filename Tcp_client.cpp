#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include "Manazer.h"
#include "Tcp_client.h"

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

char* Tcp_client::citaj(char *buffer, int newsockfd) {
    bzero(buffer, 256);
    int n = read(newsockfd, buffer, 255);
    if (n < 0) {
        perror("Error reading from socket");
        //return 4;
    }
    printf("Here is the message: %s\n", buffer);

    return buffer;
}

void Tcp_client::zapis(char *buffer, int newsockfd) {
    const char *msg = "I got your message";
    printf("Please enter a message: ");
    bzero(buffer, 256);
    fgets(buffer, 255, stdin);
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
        pthread_mutex_unlock(d->mutex);

        pthread_mutex_lock(d->mutex);
        do {
            Tcp_client::citaj(d->buffer, d->newsockfd);
        } while (*d->buffer != 'h');

        char znak = *d->buffer;
        pthread_mutex_unlock(d->mutex);

        pthread_mutex_lock(d->mutex);
        /*do {
            Tcp_server::citaj(d->buffer, d->newsockfd);
        } while (d->buffer[0] != '0' || d->buffer[0] != '1' || d->buffer[0] != '2' || d->buffer[0] != '3');
        int idFig = d->buffer[0];*/
        int idFig = 1;

        int idHraca = klientData->id;

        d->manazer.getHraci()[idHraca].vykonajTah(znak, idFig);
        d->manazer.skontrolujFigurky(idHraca);
        d->manazer.getHraciaPlocha().vykresliPlochu();

        d->aktualneId = d->manazer.getDalsiHrac(d->aktualneId, 2);
        printf("prehadzujem na server\n");
        pthread_cond_signal(d->condKlient);
        pthread_mutex_unlock(d->mutex);

    } while (d->manazer.beziHra());

    pthread_exit(nullptr);
}

int main(int argc, char **argv) {

    int sockfd, n;
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

    //TODO rovnake data
    KD klientData = {
            1, &data
    };

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

    return 0;
}
