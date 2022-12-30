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
            //cislo = hod();
            cislo = 6;
            cout << "HODIL som 6" << endl;
            while (cislo == 6) {
                //TODO chyba pri vyberani figurky, ked hrac hodi 2x 6 a nejake cislo -
                // figurka sa nastavi na startovaciu poziciu a pohne o nejake cislo

                idFigurky = vyberFigurku();
                // posun zo zakladne na startovaciu poziciu
                if (!figurky[idFigurky - 1].getJeNaHracejPloche()) {
                    while (!overTah(cislo, idFigurky)) {
                        idFigurky = vyberFigurku();
                    }
                    figurky[idFigurky - 1].setNaStartovaciuPoziciu();
                } else {
                    while (!overTah(cislo, idFigurky)) {
                        idFigurky = vyberFigurku();
                    }
                    //figurky[idFigurky - 1].posunOPolicka(cislo);
                }
                cislo = hod();
                if (cislo != 6) {
                    idFigurky = vyberFigurku();
                    idFigurky = skontrolujPoziciuFigurky(idFigurky);
                    while (!overTah(cislo, idFigurky)) {
                        idFigurky = vyberFigurku();
                    }
                    //figurky[idFigurky - 1].posunOPolicka(cislo);
                }

                pocetHodov = 0;
            }
            pocetHodov--;
        }
    } else {
        cislo = hod();
        idFigurky = vyberFigurku();
        if (cislo != 6) {
            idFigurky = skontrolujPoziciuFigurky(idFigurky);
            while (!overTah(cislo, idFigurky)) {
                idFigurky = vyberFigurku();
            }
            //figurky[idFigurky - 1].posunOPolicka(cislo);
        } else {
            while (cislo == 6) {
                if (!figurky[idFigurky - 1].getJeNaHracejPloche()) {
                    while (!overTah(cislo, idFigurky)) {
                        idFigurky = vyberFigurku();
                    }
                    figurky[idFigurky - 1].setNaStartovaciuPoziciu();
                } else {
                    while (!overTah(cislo, idFigurky)) {
                        idFigurky = vyberFigurku();
                    }
                    //figurky[idFigurky - 1].posunOPolicka(cislo);
                }
                cislo = hod();
                idFigurky = vyberFigurku();
                if (cislo != 6) {
                    idFigurky = skontrolujPoziciuFigurky(idFigurky);
                    while (!overTah(cislo, idFigurky)) {
                        idFigurky = vyberFigurku();
                    }
                    //figurky[idFigurky - 1].posunOPolicka(cislo);
                }
            }
        }
    }
}

int Hrac::skontrolujPoziciuFigurky(int idFigurky) {
    while (!figurky[idFigurky - 1].getJeNaHracejPloche()) {
        cout << "<Figurka nie je na hracej ploche!> " << endl;
        idFigurky = vyberFigurku();
    }
    return idFigurky;
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
        cout << "<Nespravny prikaz> " << endl;
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
        cout << "<Figurka neexistuje> " << endl;
        cout << "Vyber figurku >>";
        cin >> idFigurky;
    }

    return idFigurky;
}

bool Hrac::jeMoznePohnutFigurku(int id) {
    if (figurky[id - 1].getJeNaHracejPloche())
        return true;
    else if (figurky[id - 1].getJeVDomceku() || figurky[id - 1].getJeVZakladni())
        return false;

    return false;
}

////funkcia pre overenie toho, ci sa moze hrac pohnut s figurkou na zvolene miesto, kontroluje sa, ci sa na zvolenej pozicii nenachadza figurka
bool Hrac::overTah(int pocetKrokov, int id) {
    int pocitadlo = 0;
    int* povodnaPozicia = figurky[id - 1].getPoziciu();

    if (figurky[id - 1].getJeNaHracejPloche()) {
        figurky[id - 1].posunOPolicka(pocetKrokov);
        int* ocakavanaPozicia = figurky[id - 1].getPoziciu();

        for (int i = 0; i < pocetFigurok; ++i) {
            if (i != id - 1) {
                //if (*ocakavanaPozicia == *figurky[i].getPoziciu()) {
                if (ocakavanaPozicia[0] == figurky[i].getPoziciu()[0] && ocakavanaPozicia[1] == figurky[i].getPoziciu()[1]) {
                    cout << i+1 << ".figurka x,y = " << figurky[i].getPoziciu()[0] << "," << figurky[i].getPoziciu()[1] << endl;

                    figurky[id - 1].odpocitajKroky(pocetKrokov);
                    figurky[id - 1].setPoziciu(povodnaPozicia[0], povodnaPozicia[1]);
                    pocitadlo++;
                }
                cout << i+1 << ".FIGURKA x,y = " << figurky[i].getPoziciu()[0] << "," << figurky[i].getPoziciu()[1] << endl;

            }
        }
       // delete[] ocakavanaPozicia;
    } else {
        for (int i = 0; i < pocetFigurok; ++i) {
            if (i != id - 1) {
                if (figurky[i].getJeNaStartovacejPozicii()) {
                    pocitadlo++;
                    figurky[id - 1].setPoziciu(povodnaPozicia[0], povodnaPozicia[1]);
                }
            } else {
                //TODO ak je na startovacej pozicii a ocakavana sa rovna pozicii figutky tak pocitadlo++ a nastav povodnu poziciu
                /*if (figurky[id - 1].getJeNaStartovacejPozicii() &&
                    ocakavanaPozicia[0] == figurky[i].getPoziciu()[0] && ocakavanaPozicia[1] == figurky[i].getPoziciu()[1] ) {
                    pocitadlo++;
                    figurky[id - 1].setPoziciu(povodnaPozicia[0], povodnaPozicia[1]);
                }*/
            }
        }
    }

    //delete[] povodnaPozicia;

    if (pocitadlo >= 1) {
        cout << "<S danou figurkou sa nemozno pohnut!>" << endl;
        cout << "POCITADLO = " << pocitadlo << endl;
        return false;
    }

    return true;
}


