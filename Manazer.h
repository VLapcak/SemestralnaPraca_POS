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
    void dalsiHrac();
    bool beziHra();
    void vyberNahodnehoZacinajuceho();
    void skontrolujFigurky();
    void setFigurkuNaZakladnu(char farba, int idFigurky);

public:
    Manazer();
    bool posliPrikaz(int idKlienta, const std::string& prikaz);


};
#endif //SEMESTRALKA_LAPCAK_IHRING_MANAZER_H
