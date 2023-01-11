#ifndef SEMESTRALKA_LAPCAK_IHRING_HRAC_H
#define SEMESTRALKA_LAPCAK_IHRING_HRAC_H
#include "Figurka.h"
#include "Kocka.h"
#include "string"

class Hrac {

private:
    int pocetFigurok;
    int pocetFigurokDomcek;
    char farbaHraca;
    Figurka figurky[4];
    Kocka kocka;
    int vyberFigurku();
    int hod();
    bool dostupnaVZakladni();


public:
    Hrac();
    void setFarbu(char farba);
    void overPocetFigurokDomcek();
    char getFarbu();
    Figurka getFigurka(int id);
    void vykonajTah();
    bool getVyhralHru();
    bool suFigurkyNaHP();
    void setFigurkeZakladnu(int id);
    void overPozicieFigurok(int pocetKrokov, int id);
    int skontrolujCiJeNaHP(int idFigurky);
};



#endif //SEMESTRALKA_LAPCAK_IHRING_HRAC_H
