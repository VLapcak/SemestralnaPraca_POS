#ifndef SEMESTRALKA_LAPCAK_IHRING_HRAC_H
#define SEMESTRALKA_LAPCAK_IHRING_HRAC_H
#include "Figurka.h"
#include "Kocka.h"

class Hrac {

    int pocetFigurok;
    int pocetFigurokDomcek;
    char farbaHraca;
    Figurka figurky[4];
    Kocka kocka;


public:
    Hrac();
    void setFarbu(char farba);
    char getFarbu();
    Figurka getFigurka(int id);
    bool suFigurkyNaHP();
    void vykonajTah();
    int hod();
    int vyberFigurku();
    bool jeMoznePohnutFigurku(int id);
    bool overTah(int pocetKrokov, int id);

    int skontrolujPoziciuFigurky(int idFigurky);
};



#endif //SEMESTRALKA_LAPCAK_IHRING_HRAC_H
