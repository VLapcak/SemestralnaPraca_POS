#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <string>
#include <iostream>
#include "pthread.h"

using namespace std;

#define VELKOSTBUFFERA 1024


void posliSpravu(char *buffer, const char *sprava, int socket) {
    send(socket, sprava, strlen(sprava) + 1, 0);
    bzero(buffer, VELKOSTBUFFERA);
    recv(socket, buffer, VELKOSTBUFFERA, 0);
}

void prijmiSpravu(char *buffer, int socket) {
    bzero(buffer, VELKOSTBUFFERA);
    recv(socket, buffer, VELKOSTBUFFERA, 0);
    printf("%s\n", buffer);

    const char* sprava = "";
    send(socket, sprava, strlen(sprava) + 1, 0);
}

typedef struct data {
    int socket;
    char *buffer;
    char *username;

    pthread_mutex_t *mutex;
    //pthread_cond_t* cond_klient;
} DATA;

static void *komunikuj(void *args) {
    DATA *data = (DATA *) args;

    string sprava = "[HRA]: Klient ";
    sprava += data->username;
    sprava += " dostal plochu";

    prijmiSpravu(data->buffer, data->socket);
    posliSpravu(data->buffer, sprava.c_str(), data->socket);

    pthread_mutex_lock(data->mutex);

    string bufferString;
    for (int i = 0; i < 4; ++i) {
        bufferString += data->buffer[i];
    }

    while (bufferString != "end\n") {


        pthread_mutex_unlock(data->mutex);

        pthread_mutex_lock(data->mutex);
        prijmiSpravu(data->buffer, data->socket);

        bzero(data->buffer, VELKOSTBUFFERA);
        fgets(data->buffer, VELKOSTBUFFERA - 1, stdin);
        send(data->socket, data->buffer, VELKOSTBUFFERA, 0);

        for (int i = 0; i < 4; ++i) {
            bufferString += data->buffer[i];
        }

        //prijmiSpravu(buffer, sock);
        pthread_mutex_unlock(data->mutex);

        pthread_mutex_lock(data->mutex);
    }
    pthread_mutex_unlock(data->mutex);

    pthread_exit(nullptr);
}

int main(int argc, char **argv) {
    srand(time(nullptr));

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
    bzero((char *) &serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *) &serverAddress.sin_addr.s_addr, server->h_length);
    serverAddress.sin_port = htons(port);

    if (connect(sock, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
        perror("Chyba - connect.");
    }

    char buffer[VELKOSTBUFFERA];
    bzero(buffer, VELKOSTBUFFERA);

    pthread_mutex_t mutex;
    //pthread_cond_t cond_klient;
    pthread_mutex_init(&mutex, nullptr);
    //pthread_cond_init(&cond_klient, nullptr);
    DATA data = {sock, buffer, userName, &mutex};

    pthread_t klientVlakno;
    pthread_create(&klientVlakno, nullptr, komunikuj, &data);

    pthread_join(klientVlakno, nullptr);


    close(sock);

    return (EXIT_SUCCESS);

}

