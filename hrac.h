#ifndef SEMESTRALKA_LAPCAK_IHRING_HRAC_H
#define SEMESTRALKA_LAPCAK_IHRING_HRAC_H
#include "figurka.h"

class hrac {


    int pocetFigurok;
    int pocetFigurokDomcek;
    char farbaHraca;
    figurka figurky[4];

public:
    hrac();
    void setFarbu(char farba);
    char getFarbu();
    figurka getFigurka(int id) const;
};



#endif //SEMESTRALKA_LAPCAK_IHRING_HRAC_H
