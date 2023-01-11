#ifndef SEMESTRALKA_LAPCAK_IHRING_TCP_SERVER_H
#define SEMESTRALKA_LAPCAK_IHRING_TCP_SERVER_H


#include "Kocka.h"

class Tcp_server {
    int create_server(int argc, char *argv[]);
    static void *hrajServer(void *args);
    Kocka kocka;

public:
    Tcp_server(int argc, char *argv[]);
    void overenieVstupu(char* buffer, int socket);
    int hod(char* buffer, int socket);
};


#endif //SEMESTRALKA_LAPCAK_IHRING_TCP_SERVER_H
