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
    for (int i = 0; i < 100; ++i) {
        hraci[idAktualnehoHraca].vykonajTah();
        hp.vykresliPlochu();
        dalsiHrac();
    }

    ////Pre test jedneho hraca
    /*for (int i = 0; i < 20; ++i) {
        hraci[0].vykonajTah();
        hp.vykresliPlochu();
    }*/



    // bude sa cakat dovtedy kym pocet pripojenych hracov nebude 4
    /*pthread_mutex_lock()
    while (pocetPripojenychHracov < 4) {
        pthread_cond_wait()
    }
    pthread_cond_broadcast()
    pthread_mutex_unlock()*/

}

void Manazer::beziHra() {

}
void Manazer::dalsiHrac() {
    if (idAktualnehoHraca < 3 )
        idAktualnehoHraca++;
    else
        idAktualnehoHraca = 0;

    printf("%s %c %s", "Na rade je", hraci[idAktualnehoHraca].getFarbu(), "hrac \n");

}

void Manazer::vyberNahodnehoZacinajuceho() {
    idAktualnehoHraca = rand() % 3 + 0;
}


