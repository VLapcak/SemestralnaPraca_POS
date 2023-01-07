#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
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

int main(int argc, char **argv) {
    srand(time(nullptr));

    int sockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    DATA data;

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

    while (true) {
        DATA d;


        data.manazer.getHraciaPlocha().vykresliPlochu();
        printf("Klient zadaj spravu: ");
        int id = data.manazer.getHraci()[data.aktualneId].vykonajTah();
        data.manazer.skontrolujFigurky(id);
        data.manazer.getHraciaPlocha().vykresliPlochu();
        printf("prehadzujem na server\n");
        data.aktualneId = data.manazer.getDalsiHrac(data.aktualneId, 2);

        /*bzero(buffer, 256);
        fgets(buffer, 255, stdin);*/

        n = write(sockfd, &data, sizeof(DATA));
        //n = write(sockfd, buffer, strlen(buffer));
        if (n < 0) {
            perror("Error writing to socket");
            return 5;
        }

        //bzero(buffer, 256);
        //n = read(sockfd, buffer, 255);
        n = read(sockfd, &data, 255);
        if (n < 0) {
            perror("Error reading from socket");
            return 6;
        }



        printf("%s\n", buffer);
    }
    close(sockfd);

    return 0;
}
