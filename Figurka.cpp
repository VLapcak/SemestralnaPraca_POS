#include "Figurka.h"
#include "iostream"

using namespace std;

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

    if (naStartovacejPozicii) {
        naStartovacejPozicii = false;
    }

    if ((pocetKrokov + pocet) > 44) {       //po 39 krokoch je figurka pred domcekom (domcek - > 40, 41, 42, 43)
        printf("%s %c %c %s", "Figurka ", farbaFigurky, idFigurky, " sa nemôže sa pohnúť do domceka.\n");

    } else {
        for (int i = 0; i < pocet; ++i) {
            if (pocetKrokov < 39) {

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
                //TODO Potom odstranit
                cout << "xy = " << poziciaXY[0] << ", " << poziciaXY[1] << " -> ";
                pocetKrokov++;
            } else {

                switch (farbaFigurky) {
                    case 'C': poziciaXY[0]++;
                        break;
                    case 'M': poziciaXY[1]--;
                        break;
                    case 'B': poziciaXY[0]--;
                        break;
                    case 'Z': poziciaXY[1]++;
                        break;
                }
                jeNaHracejPloche = false;
                jeVZakladni = false;
                jeVDomceku = true;
            }
        }
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


void Figurka::setNaStartovaciuPoziciu() {

    naStartovacejPozicii = true;
    jeNaHracejPloche = true;
    jeVZakladni = false;
    switch (farbaFigurky) {
        case 'C':
            poziciaXY[0] = startovaciePozicie[0][0];
            poziciaXY[1] = startovaciePozicie[0][1];
            break;
        case 'Z':
            poziciaXY[0] = startovaciePozicie[1][0];
            poziciaXY[1] = startovaciePozicie[1][1];
            break;
        case 'B':
            poziciaXY[0] = startovaciePozicie[2][0];
            poziciaXY[1] = startovaciePozicie[2][1];
            break;
        case 'M':
            poziciaXY[0] = startovaciePozicie[3][0];
            poziciaXY[1] = startovaciePozicie[3][1];
            break;
        default:
            break;
    }
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

void Figurka::odpocitajKroky(int pocet) {
    pocetKrokov -= pocet;
}
