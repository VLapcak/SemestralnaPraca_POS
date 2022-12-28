#include "Figurka.h"
#include "iostream"

Figurka::Figurka() {

    poziciaXY = new int[2];
    farbaFigurky = 'X';
    idFigurky = 0;
    jeVZakladni = true;
    naStartovacejPozicii = false;
    jeNaHracejPloche = false;
    jeVDomceku = false;
    pocetKrokov = 0;
}

void Figurka::posunOPolicka(int pocet) {

    for (int i = 0; i < pocet; ++i) {

        if ((poziciaXY[0] < 4 && poziciaXY[1] == 4) ||
            (poziciaXY[0] < 6 && poziciaXY[1] == 0) ||
            ((poziciaXY[0] >= 6 && poziciaXY[0] < 10) && poziciaXY[1] == 4)) {
            poziciaXY[0]++;
        } else if ((poziciaXY[0] > 6 && poziciaXY[1] == 6) ||
                   ((poziciaXY[0] > 4) && poziciaXY[1] == 10) ||
                    ((poziciaXY[0] <= 4 && poziciaXY[0] > 0) && poziciaXY[1] == 6)) {
            poziciaXY[0]--;
        } else if ((poziciaXY[0] == 4 && poziciaXY[1] > 6) ||
                   (poziciaXY[0] == 0 && poziciaXY[1] <= 6) ||
                   ((poziciaXY[0] == 4) && poziciaXY[1] <= 4)) {
            poziciaXY[1]--;
        } else if ((poziciaXY[0] == 6 && poziciaXY[1] < 4) ||
                   (poziciaXY[0] == 10 && poziciaXY[1] <= 6) ||
                   ((poziciaXY[0] == 6) && poziciaXY[1] >= 6)) {
            poziciaXY[1]++;
        }
        std::cout << "xy = " << poziciaXY[0] << ", " << poziciaXY[1] << std::endl;
        pocetKrokov += pocet;

        //TODO po kazdom pohybe figurky manazer vykresli hraciu plochu
    }
}

//setteri
void Figurka::setFarbu(char farba) {
    farbaFigurky = farba;
}

void Figurka::setPoziciu(int x, int y) {
    poziciaXY[0] = x;
    poziciaXY[1] = y;
}

void Figurka::setIDFigurky(int cislo) {
    idFigurky = cislo;
}


void Figurka::setJeNaHracejPloche(bool stav) {
    jeNaHracejPloche = stav;
}


void Figurka::setJeNaStartovacejPozicii(bool stav) {
    naStartovacejPozicii = stav;
}


void Figurka::setJeVDomceku(bool stav) {
    jeVDomceku = stav;
}

void Figurka::setJeVZakladni(bool stav) {
    jeVZakladni = stav;
}


//gettere
int *Figurka::getPoziciu() {

    return poziciaXY;
}

bool Figurka::getJeVZakladni() {
    return jeVZakladni;
}

bool Figurka::getJeNaHracejPloche() {
    return jeNaHracejPloche;
}

bool Figurka::getJeVDomceku() {
    return jeVDomceku;
}

int Figurka::getIDFigurky() {
    return idFigurky;
}

bool Figurka::getJeNaStartovacejPozicii() {
    return naStartovacejPozicii;
}

int *Figurka::getStartovaciePozicie(char farba) {
    switch (farba) {
        case 'C':
            return startovaciePozicie[0];
        case 'Z':
            return startovaciePozicie[1];
        case 'B':
            return startovaciePozicie[2];
        case 'M':
            return startovaciePozicie[3];
        default:
            return nullptr;
    }
}



