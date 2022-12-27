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

}

void Figurka::posunOPolicka(int pocet) {

    for (int i = 0; i < pocet; ++i) {

        if (poziciaXY[0] == 4 && poziciaXY[1] <= 4) {
            poziciaXY[1]--;
        } else
            poziciaXY[0]++;
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



