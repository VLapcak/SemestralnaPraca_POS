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
            if (cislo == 6) {
                while (cislo == 6) {
                    idFigurky = vyberFigurku();


                    //TODO ak hodi hrac 6 6 5 a s 1. sa pohne na SP a s 2. chce ist na SP
                    if (figurky[idFigurky - 1].getJeNaStartovacejPozicii()) {
                        figurky[idFigurky - 1].posunOPolicka(cislo); // sp = false

                    } else {

                        if (figurky[idFigurky - 1].getJeNaHracejPloche()) {
                            figurky[idFigurky - 1].posunOPolicka(cislo); // sp = false

                        } else {
                            if (figurky[idFigurky - 1].getJeVZakladni()) {
                                int pocitadlo = 1;
                                while (pocitadlo != 0) {
                                    pocitadlo = 0;
                                    for (int i = 0; i < pocetFigurok; ++i) {
                                        if (i != idFigurky - 1) {
                                            if (figurky[i].getJeNaStartovacejPozicii()) {
                                                pocitadlo++;
                                            }
                                        }
                                    }
                                    if (pocitadlo > 0) {
                                        printf("<S danou figurkou sa nemozno pohnut> \n");
                                        idFigurky = vyberFigurku();
                                    }
                                }
                                figurky[idFigurky - 1].setNaStartovaciuPoziciu();// sp = true
                            }

                        }
                    }
                    cislo = hod();

                    pocetHodov = 0;
                }
                figurky[idFigurky - 1].posunOPolicka(cislo);
            }
            pocetHodov--;
        }
    } else { //ak je uz nejaka figurka na hracej ploche

        // ak je nejaka figurka na SP tak tam ina nemoze ist
        cislo = hod();
        if (cislo == 6) {
            while (cislo == 6) {
                idFigurky = vyberFigurku();

                if (figurky[idFigurky - 1].getJeVZakladni()) {
                    int pocitadlo = 1;

                    while (pocitadlo != 0) {
                        pocitadlo = 0;
                        for (int i = 0; i < pocetFigurok; ++i) {
                            if (i != idFigurky - 1) {
                                if (figurky[i].getJeNaStartovacejPozicii()) {
                                    pocitadlo++;
                                }
                            }
                        }
                        if (pocitadlo > 0) {
                            printf("<S danou figurkou sa nemozno pohnut> \n");
                            idFigurky = vyberFigurku();
                        }
                    }
                    if (!figurky[idFigurky - 1].getJeNaStartovacejPozicii())
                        figurky[idFigurky - 1].setNaStartovaciuPoziciu();
                    else if (figurky[idFigurky - 1].getJeNaHracejPloche()) {
                        break;
                    }
                } else if (figurky[idFigurky - 1].getJeNaStartovacejPozicii() ||
                    figurky[idFigurky - 1].getJeNaHracejPloche()) {
                    overPozicieFigurok(cislo, idFigurky);
                }
                cislo = hod();
            }
            idFigurky = vyberFigurku();
            idFigurky = skontrolujCiJeNaHP(idFigurky);
            overPozicieFigurok(cislo, idFigurky);
        } else {
            idFigurky = vyberFigurku();
            idFigurky = skontrolujCiJeNaHP(idFigurky);
            overPozicieFigurok(cislo, idFigurky);
        }

    }
}

int Hrac::skontrolujCiJeNaHP(int idFigurky) {
    while (!figurky[idFigurky - 1].getJeNaHracejPloche()) {
        printf("<Figurka nie je na hracej ploche!> \n");
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
        printf("<Nespravny prikaz> \n");
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

void Hrac::overPozicieFigurok(int pocetKrokov, int id) {
    id--;
    int pocitadlo = 1;
    int *povodnaPozicia = new int[2];
    int *ocakavanaPozicia = new int[2];

    while (pocitadlo != 0) {
        pocitadlo = 0;
        povodnaPozicia[0] = figurky[id].getPoziciu()[0];
        povodnaPozicia[1] = figurky[id].getPoziciu()[1];

        figurky[id].posunOPolicka(pocetKrokov);

        ocakavanaPozicia[0] = figurky[id].getPoziciu()[0];
        ocakavanaPozicia[1] = figurky[id].getPoziciu()[1];

        for (int i = 0; i < pocetFigurok; ++i) {
            if (i != id) {
                if (ocakavanaPozicia[0] == figurky[i].getPoziciu()[0] &&
                    ocakavanaPozicia[1] == figurky[i].getPoziciu()[1]) {
                    figurky[id].odpocitajKroky(pocetKrokov);
                    figurky[id].setPoziciu(povodnaPozicia[0], povodnaPozicia[1]);
                    pocitadlo++;
                }
            }
        }
        if (pocitadlo > 0) {
            printf("<S danou figurkou sa nemozno pohnut> \n");
            id = vyberFigurku();
            id = skontrolujCiJeNaHP(id) - 1;
        }
    }
}


