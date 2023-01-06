#ifndef SEMESTRALKA_LAPCAK_IHRING_MANAZER_H
#define SEMESTRALKA_LAPCAK_IHRING_MANAZER_H

#include "HraciaPlocha.h"
#include "string"

class Manazer {

private:
    int pocetHracov;
    Hrac hraci[4];
    HraciaPlocha hp;
    char farby[4]{'C', 'M', 'B', 'Z'};
    int idAktualnehoHraca;
    int pocetPripojenychHracov;

    bool beziHra();
    void vyberNahodnehoZacinajuceho();
    void skontrolujFigurky(int id);
    void setFigurkuNaZakladnu(char farba, int idFigurky);

public:
    Manazer();
    void dalsiHrac(int aktualneID);
    void* hraj(void * args);
    void* hrajKlient(void * args);

    static void* run_server(void* ptr);
    static void* run_klient(void* ptr);
};
#endif //SEMESTRALKA_LAPCAK_IHRING_MANAZER_H
