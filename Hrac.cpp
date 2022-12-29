#include "Hrac.h"
#include <iostream>
#include <limits>

using namespace std;

Hrac::Hrac() {
    pocetFigurok = 4;
    pocetFigurokDomcek = 0;
    farbaHraca = 'X';

    for (int i = 0; i < pocetFigurok; ++i) {
        figurky[i] = *new Figurka();
        figurky[i].setIDFigurky(i + 1);
    }
}

void Hrac::setFarbu(char farba) {

    farbaHraca = farba;
    for (int i = 0; i < pocetFigurok; ++i) {
        figurky[i].setFarbu(farbaHraca);
    }
}


Figurka Hrac::getFigurka(int id) {
    return figurky[id];
}

char Hrac::getFarbu() {
    return farbaHraca;
}

void Hrac::vykonajTah() {
    int cislo = 0;
    int idFigurky = 0;
    if (!suFigurkyNaHP()) {
        //Hrac hadze maximalne 3x dovtedy kym nehodi 6
        //ak hodi 6 tak sa postavi na startovaciu poziciu a hadze znovu
        int pocetHodov = 3;
        while (pocetHodov > 0) {
            cislo = hod();
            while (cislo == 6) {
                idFigurky = vyberFigurku();
                // posun zo zakladne na startovaciu poziciu
                if (!figurky[idFigurky - 1].getJeNaHracejPloche()) {
                    figurky[idFigurky - 1].setNaStartovaciuPoziciu();
                    figurky[idFigurky - 1].setJeNaHracejPloche(true);
                    figurky[idFigurky - 1].setJeVZakladni(false);
                    cislo = hod();
                }
                if (figurky[idFigurky - 1].getJeNaHracejPloche()) {
                    figurky[idFigurky - 1].posunOPolicka(cislo);
                    figurky[idFigurky - 1].setJeNaStartovacejPozicii(false);
                }
                pocetHodov = 0;
            }
            pocetHodov--;
        }
    } else {
        cislo = hod();
        idFigurky = vyberFigurku();
        if (cislo != 6) {
            while (!figurky[idFigurky - 1].getJeNaHracejPloche()) {
                cout << "<Figurka nie je na hracej ploche!> ";
                idFigurky = vyberFigurku();
            }
            figurky[idFigurky - 1].posunOPolicka(cislo);
        } else if (!figurky[idFigurky - 1].getJeNaHracejPloche()) {
            figurky[idFigurky - 1].setNaStartovaciuPoziciu();
            figurky[idFigurky - 1].setJeNaHracejPloche(true);
            figurky[idFigurky - 1].setJeVZakladni(false);
        }
        while (cislo == 6) {
            cislo = hod();
            idFigurky = vyberFigurku();
            figurky[idFigurky - 1].posunOPolicka(cislo);
        }
    }
}

bool Hrac::suFigurkyNaHP() {
    int pocetFigurokNaHracejPloche = 0;
    for (int i = 0; i < pocetFigurok; ++i) {
        if (figurky[i].getJeNaHracejPloche()) {
            pocetFigurokNaHracejPloche++;
        }
    }
    if (pocetFigurokNaHracejPloche > 0) {
        return true;
    }
    return false;
}

int Hrac::hod() {
    cout << ">>";
    string hod;
    cin >> hod;
    while (hod != "hod") {
        cout << "<Nespravny prikaz> ";
        cout << ">>";
        cin >> hod;
    }
    int cislo = kocka.getCislo();
    cout << "Hodil si: " << cislo << endl;
    return cislo;
}

int Hrac::vyberFigurku() {
    cout << "Vyber figurku >>";
    int idFigurky;
    cin >> idFigurky;

    while ((idFigurky - 1) > 3 || (idFigurky - 1) < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "<Figurka neexistuje> ";
        cout << "Vyber figurku >>";
        cin >> idFigurky;
    }

    //TODO podmienka pre zvolenie figúrky na ploche ak uz ma na hracej ploche nejaku
    return idFigurky;
}

bool Hrac::jeMoznePohnutFigurku(int id) {
    if (figurky[id - 1].getJeNaHracejPloche())
        return true;
    else if (figurky[id - 1].getJeVDomceku() || figurky[id - 1].getJeVZakladni())
        return false;

    return false;
}


