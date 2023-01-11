#ifndef SEMESTRALKA_LAPCAK_IHRING_MANAZER_H
#define SEMESTRALKA_LAPCAK_IHRING_MANAZER_H

#include "HraciaPlocha.h"
#include "string"

class Manazer {

private:
    Hrac hraci[4];
    HraciaPlocha hp;
    int pocetHracov;
    char farby[4]{'C', 'M', 'B', 'Z'};
    int idAktualnehoHraca;
    int pocetPripojenychHracov;
    void vyberNahodnehoZacinajuceho();
    void setFigurkuNaZakladnu(char farba, int idFigurky);

public:
    Manazer();
    int getDalsiHrac(int aktualneID, int maxHracov);
    bool beziHra();
    void skontrolujFigurky(int id);
    Hrac* getHraci();
    std::string getPlocha();
};
#endif //SEMESTRALKA_LAPCAK_IHRING_MANAZER_H
