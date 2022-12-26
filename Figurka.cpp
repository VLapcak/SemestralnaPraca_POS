#include "Figurka.h"
#include "iostream"

Figurka::Figurka() {

    poziciaXY = new int[2];
    farbaFigurky = 'X';
    jeVZakladni = true;
    jeNaStartovacejPozicii = false;
    jeNaHracejPloche = false;
    jeVDomceku = false;

}

void Figurka::posunOPolicka(int pocet) {

    for (int i = 0; i < pocet; ++i) {

       if (poziciaXY[0] == 4 && poziciaXY[1] <= 4)
       {
           poziciaXY[1]--;
       }
       else
           poziciaXY[0]++;
    }
}

void Figurka::setFarbu(char farba) {
    farbaFigurky = farba;
}

void Figurka::setPoziciu(int x, int y) {
    poziciaXY[0] = x;
    poziciaXY[1] = y;
}

int *Figurka::getPoziciu() {

    return poziciaXY;
}

bool Figurka::getJeVZakladni() {
    return jeVZakladni;
}

bool Figurka::getJeNaStartovacejPozicii() {
    return jeNaStartovacejPozicii;
}

bool Figurka::getJeNaHracejPloche() {
    return jeNaHracejPloche;
}

bool Figurka::getJeVDomceku() {
    return jeVDomceku;
}
