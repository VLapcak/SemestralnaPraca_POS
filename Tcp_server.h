#ifndef SEMESTRALKA_LAPCAK_IHRING_TCP_SERVER_H
#define SEMESTRALKA_LAPCAK_IHRING_TCP_SERVER_H


#include "Kocka.h"
#include "Hrac.h"
#include "Manazer.h"

class Tcp_server {
    int create_server(int argc, char *argv[], Manazer manazer);
    static void *hrajServer(void *args);
    Kocka kocka;
    Hrac hraci[4];
    int idAktualnehoHraca;
    void posliSpravu(std::string sprava, int socket);
    void prijmiSpravu(char* buffer, int socket);

public:
    Tcp_server(int argc, char *argv[]);
    void overenieVstupu(char* buffer, int socket, int idHraca);
    int hod(char* buffer, int socket);
    int vyberFigurku(char *buffer, int socket);
};


#endif //SEMESTRALKA_LAPCAK_IHRING_TCP_SERVER_H
