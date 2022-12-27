#ifndef SEMESTRALKA_LAPCAK_IHRING_MANAZER_H
#define SEMESTRALKA_LAPCAK_IHRING_MANAZER_H

#include "HraciaPlocha.h"


class Manazer {
    int pocetHracov;
    Hrac hraci[4];
    char farby[4]{'C', 'M', 'Z', 'B'};
    int pocetPripojenychHracov;

public:
    Manazer();
    char naTahuJeHrac();
};





#endif //SEMESTRALKA_LAPCAK_IHRING_MANAZER_H
