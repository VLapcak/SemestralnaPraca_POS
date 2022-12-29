#ifndef SEMESTRALKA_LAPCAK_IHRING_MANAZER_H
#define SEMESTRALKA_LAPCAK_IHRING_MANAZER_H

#include "HraciaPlocha.h"


class Manazer {
    int pocetHracov;
    Hrac hraci[4];
    char farby[4]{'C', 'M', 'B', 'Z'};
    int idAktualnehoHraca;
    int pocetPripojenychHracov;

public:
    Manazer();
    void dalsiHrac();
    void beziHra();
    void vyberNahodnehoZacinajuceho();
};





#endif //SEMESTRALKA_LAPCAK_IHRING_MANAZER_H
