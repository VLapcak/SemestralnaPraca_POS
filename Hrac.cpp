#include "Hrac.h"

Hrac::Hrac() {
    pocetFigurok = 4;
    pocetFigurokDomcek = 0;
    farbaHraca = 'X';

    for (int i = 0; i < pocetFigurok; ++i) {
        figurky[i] = *new Figurka();
        figurky[i].setFarbu(farbaHraca);
    }
}

void Hrac::setFarbu(char farba) {

    farbaHraca = farba;
}


Figurka Hrac::getFigurka(int id) const {
    return figurky[id];
}

char Hrac::getFarbu() {
    return farbaHraca;
}


