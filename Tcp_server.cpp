#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include "Tcp_server.h"
#include "Manazer.h"

typedef struct {
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

int Tcp_server::create_server(int argc, char **argv) {

    //Manazer manazer = Manazer();
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

    //spustam hru
    Manazer manazer = Manazer();

    pthread_t klient;
    pthread_t server;
    pthread_mutex_t  mutex;
    pthread_cond_t condServer;
    pthread_cond_t condKlient;

    pthread_mutex_init(&mutex, nullptr);
    pthread_cond_init(&condServer, nullptr);
    pthread_cond_init(&condKlient, nullptr);

    DATA data = {
            0, &mutex, &condServer, &condKlient
    };
    SD serverData = {
            0, &data
    };
    KD klientData = {
            1, &data
    };

    pthread_create(&klient, nullptr, &Manazer::run_klient, &klientData);
    pthread_create(&server, nullptr, &Manazer::run_server, &serverData);

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

    return 0;
}

Tcp_server::Tcp_server(int argc, char **argv) {
    create_server(argc, argv);
}

void *Tcp_server::hrajHru(void *args) {
    return nullptr;
}

