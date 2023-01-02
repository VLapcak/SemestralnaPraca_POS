#ifndef SEMESTRALKA_LAPCAK_IHRING_HRAC_H
#define SEMESTRALKA_LAPCAK_IHRING_HRAC_H
#include "Figurka.h"
#include "Kocka.h"

class Hrac {

private:
    int pocetFigurok;
    int pocetFigurokDomcek;
    char farbaHraca;
    Figurka figurky[4];
    Kocka kocka;
    int vyberFigurku();
    int hod();
    bool suFigurkyNaHP();
    void overPozicieFigurok(int pocetKrokov, int id);
    int skontrolujCiJeNaHP(int idFigurky);
    bool dostupnaVZakladni();


public:
    Hrac();
    void setFarbu(char farba);
    char getFarbu();
    Figurka getFigurka(int id);
    void vykonajTah();
    bool getVyhralHru();
    void setFigurkeZakladnu(int id);
};



#endif //SEMESTRALKA_LAPCAK_IHRING_HRAC_H
