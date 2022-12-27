#include "Manazer.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

Manazer::Manazer() {
    pocetHracov = 4;
    pocetPripojenychHracov = 0;

    for (int i = 0; i < pocetHracov; ++i) {
        hraci[i] = *new Hrac();
        hraci[i].setFarbu(farby[i]);
    }
    HraciaPlocha hp = *new HraciaPlocha(hraci);
    hp.vykresliPlochu();

    // bude sa cakat dovtedy kym pocet pripojenych hracov nebude 4
    /*pthread_mutex_lock()
    while (pocetPripojenychHracov < 4) {
        pthread_cond_wait()
    }
    pthread_cond_broadcast()
    pthread_mutex_unlock()*/

}

char Manazer::naTahuJeHrac() {


    return 0;
}

