#include "Manazer.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

Manazer::Manazer() {
    pocetHracov = 4;
    pocetPripojenychHracov = 0;
    idAktualnehoHraca = 0;

    for (int i = 0; i < pocetHracov; ++i) {
        hraci[i] = *new Hrac();
        hraci[i].setFarbu(farby[i]);
    }
    HraciaPlocha hp = *new HraciaPlocha(hraci);
    hp.setZakladnaPlocha();
    hp.vykresliPlochu();

    ////Pre test viacerych hracov - NEMAZAT!!!
    vyberNahodnehoZacinajuceho();
    printf("%s %c %s", "Na rade je", hraci[idAktualnehoHraca].getFarbu(), "hrac \n");
    do {
        hraci[idAktualnehoHraca].vykonajTah();
        //hp.skontrolujVyhodeneFigurky();
        hp.vykresliPlochu();
        dalsiHrac();
    } while (beziHra());

    // bude sa cakat dovtedy kym pocet pripojenych hracov nebude 4
    /*pthread_mutex_lock()
    while (pocetPripojenychHracov < 4) {
        pthread_cond_wait()
    }
    pthread_cond_broadcast()
    pthread_mutex_unlock()*/

}

bool Manazer::beziHra() {
    for (int i = 0; i < pocetHracov; ++i) {
        if (hraci[i].getVyhralHru()) {
            printf("%s\n", "---Hra sa skoncila---");
            printf("%s %c %s", "---Vyhral", farby[i], "hrac---");
            return false;
        }
    }
    return true;
}

void Manazer::dalsiHrac() {
    if (idAktualnehoHraca < 3)
        idAktualnehoHraca++;
    else
        idAktualnehoHraca = 0;

    printf("%s %c %s", "Na rade je", hraci[idAktualnehoHraca].getFarbu(), "hrac \n");

}

void Manazer::vyberNahodnehoZacinajuceho() {
    idAktualnehoHraca = rand() % 3 + 0;
}


