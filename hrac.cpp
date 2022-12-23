#include "hrac.h"

hrac::hrac() {
    pocetFigurok = 4;
    pocetFigurokDomcek = 0;
    farbaHraca = 'X';

    for (int i = 0; i < pocetFigurok; ++i) {
        figurky[i] = *new figurka();
        figurky[i].setFarbu(farbaHraca);
    }
}

void hrac::setFarbu(char farba) {

    farbaHraca = farba;
}


figurka hrac::getFigurka(int id) const {
    return figurky[id];
}

char hrac::getFarbu() {
    return farbaHraca;
}


