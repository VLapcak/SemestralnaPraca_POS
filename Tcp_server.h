#ifndef SEMESTRALKA_LAPCAK_IHRING_TCP_SERVER_H
#define SEMESTRALKA_LAPCAK_IHRING_TCP_SERVER_H


#include "Kocka.h"
#include "Hrac.h"
#include "Manazer.h"

using namespace std;

class Tcp_server {
    int create_server(int argc, char *argv[], Manazer manazer);
    void *obsluhaKlienta(void *args);
    Kocka kocka;
    Hrac* hraci[4];
    int idAktualnehoHraca;
    void posliSpravu(string sprava, int socket);
    void prijmiSpravu(char* buffer, int socket);

public:
    Tcp_server(int argc, char *argv[]);
    void overenieVstupu(char* buffer, int socket, int idHraca);
    int hod(char* buffer, int socket);
    int vyberFigurku(char* buffer, int socket);
    void *execute();
    void *threadFunc(void *);
};


#endif //SEMESTRALKA_LAPCAK_IHRING_TCP_SERVER_H
