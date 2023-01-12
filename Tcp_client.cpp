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

static void* hrajKlient(void *args) {

    return nullptr;
}

void posliSpravu(const char* sprava, int socket) {
    send(socket, sprava, strlen(sprava) + 1, 0);
}

void prijmiSpravu(char* buffer, int socket) {
    bzero(buffer, VELKOSTBUFFERA);
    recv(socket, buffer, VELKOSTBUFFERA, 0);
    printf("%s\n", buffer);
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

    char buffer[VELKOSTBUFFERA];
    bzero(buffer, VELKOSTBUFFERA);
    prijmiSpravu(buffer, sock);
    posliSpravu("[HRA]: Klient dostal plochu", sock);

    do {
        prijmiSpravu(buffer, sock);

        bzero(buffer,VELKOSTBUFFERA);
        fgets(buffer, VELKOSTBUFFERA-1, stdin);
        send(sock, buffer, VELKOSTBUFFERA, 0);
        //prijmiSpravu(buffer, sock);

    } while (strcmp(buffer, "end") != 0);

    close(sock);

    return (EXIT_SUCCESS);

}

