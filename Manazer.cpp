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
    hp.setHracov(hraci);
    hp.setZakladnaPlocha();
    hp.vykresliPlochu();

    ////Pre test viacerych hracov - NEMAZAT!!!
    vyberNahodnehoZacinajuceho();
    printf("\n%s %c %s", "-------------Na rade je", hraci[idAktualnehoHraca].getFarbu(), "hrac-------------- \n");
    do {
        hraci[idAktualnehoHraca].vykonajTah();
        skontrolujFigurky();
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

    printf("\n%s %c %s", "-------------Na rade je", hraci[idAktualnehoHraca].getFarbu(), "hrac-------------- \n");

}

void Manazer::vyberNahodnehoZacinajuceho() {
    idAktualnehoHraca = rand() % 3 + 0;
}

void Manazer::skontrolujFigurky() {

    for (int f = 0; f < 4; ++f) {
        if (hraci[idAktualnehoHraca].getFigurka(f).getJeNaHracejPloche()) { // figurky aktualne iduceho hraca

            for (int i = 0; i < pocetHracov; ++i) {
                for (int j = 0; j < 4; ++j) { // nepriatelske figurky

                    if (i != idAktualnehoHraca) {
                        // aktualny hrac na tahu        v porovnani s ostatnymi hracmi a ich figurkami
                        if (hraci[idAktualnehoHraca].getFigurka(f).getPoziciu()[0] == hraci[i].getFigurka(j).getPoziciu()[0]
                            && hraci[idAktualnehoHraca].getFigurka(f).getPoziciu()[1] == hraci[i].getFigurka(j).getPoziciu()[1]) {

                            hraci[i].setFigurkeZakladnu(j);
                            setFigurkuNaZakladnu(farby[i], j);
                            printf("%c%d %s %c%d", farby[idAktualnehoHraca], f + 1, "vyhodil", farby[i], j + 1);
                        }
                    }
                }
            }
        }
    }
}


void Manazer::setFigurkuNaZakladnu(char farba, int idFigurky) {
    int* pozicia = hp.getPoziciuZakladne(farba, idFigurky);
    switch (farba) {
        case 'C':
            hraci[0].getFigurka(idFigurky).setPoziciu(pozicia[0], pozicia[1]);
            break;
        case 'M':
            hraci[1].getFigurka(idFigurky).setPoziciu(pozicia[0], pozicia[1]);
            break;
        case 'B':
            hraci[2].getFigurka(idFigurky).setPoziciu(pozicia[0], pozicia[1]);
            break;
        case 'Z':
            hraci[3].getFigurka(idFigurky).setPoziciu(pozicia[0], pozicia[1]);
            break;

        default:
            printf("<Error, zle zadana farba>");
            break;
    }
}




