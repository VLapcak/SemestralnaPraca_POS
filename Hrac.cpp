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
            //cislo = 6;
            //cout << "HODIL som 6" << endl;
            if (cislo == 6) {
                //idFigurky = vyberFigurku();
                while (cislo == 6) {
                    idFigurky = vyberFigurku();
                    bool validnyTah = false;

                    while (!validnyTah) {
                        int pocitadlo = 0;
                        if (figurky[idFigurky - 1].getJeVZakladni()) {
                            for (int i = 0; i < pocetFigurok; ++i) {
                                if (i != idFigurky - 1) {
                                    if (figurky[i].getJeNaStartovacejPozicii()) {
                                        pocitadlo++;
                                    }
                                }
                            }
                            if (pocitadlo > 0) {
                                printf("%s", "<S danou figurkou sa nemozno pohnut> \n");
                                idFigurky = vyberFigurku();
                            } else {
                                figurky[idFigurky - 1].setNaStartovaciuPoziciu();
                                validnyTah = true;
                            }
                        } else if (figurky[idFigurky - 1].getJeNaStartovacejPozicii() ||
                                   figurky[idFigurky - 1].getJeNaHracejPloche()) {
                            overPozicieFigurok(cislo, idFigurky);
                            validnyTah = true;
                        } else if (figurky[idFigurky - 1].getJeVDomceku()) {
                            printf("%s", "<Figurka sa nemoze pohnut z domceka> \n");
                            idFigurky = vyberFigurku();
                        }
                    }
                    cislo = hod();

                    pocetHodov = 0;
                }
                idFigurky = vyberFigurku();
                idFigurky = skontrolujCiJeNaHP(idFigurky);
                figurky[idFigurky - 1].posunOPolicka(cislo);
            }
            pocetHodov--;
        }
    } else { //ak je uz nejaka figurka na hracej ploche

        // ak je nejaka figurka na SP tak tam ina nemoze ist
        cislo = hod();
        if (cislo == 6) {
            //idFigurky = vyberFigurku();
            while (cislo == 6) {
                bool validnyTah = false;
                idFigurky = vyberFigurku();
                while (!validnyTah) {
                    int pocitadlo = 0;
                    if (figurky[idFigurky - 1].getJeVZakladni()) {
                        for (int i = 0; i < pocetFigurok; ++i) {
                            if (i != idFigurky - 1) {
                                if (figurky[i].getJeNaStartovacejPozicii()) {
                                    pocitadlo++;
                                }
                            }
                        }
                        if (pocitadlo > 0) {
                            printf("%s", "<S danou figurkou sa nemozno pohnut> \n");
                            idFigurky = vyberFigurku();
                        } else {
                            figurky[idFigurky - 1].setNaStartovaciuPoziciu();
                            validnyTah = true;
                        }

                    } else if (figurky[idFigurky - 1].getJeNaStartovacejPozicii() ||
                               figurky[idFigurky - 1].getJeNaHracejPloche()) {
                        overPozicieFigurok(cislo, idFigurky);
                        validnyTah = true;
                    } else if (figurky[idFigurky - 1].getJeVDomceku()) {
                        printf("%s", "<Figurka sa nemoze pohnut z domceka> \n");
                        idFigurky = vyberFigurku();
                    }
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
    pocetFigurokDomcek = 0;
    for (int i = 0; i < pocetFigurok; ++i) {
        if (figurky[i].getJeVDomceku()) {
            pocetFigurokDomcek++;
        }
    }
}

int Hrac::skontrolujCiJeNaHP(int idFigurky) {
    while (!figurky[idFigurky - 1].getJeNaHracejPloche()) {
        printf("%s", "<Figurka nie je na hracej ploche!> \n");
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
    printf("%s", "Hod kockou >> ");
    string hod;
    cin >> hod;
    while (hod != "hod") {
        printf("%s", "<Nespravny prikaz> \n");
        printf("%s", "Hod kockou >> ");
        cin >> hod;
    }
    int cislo = kocka.getCislo();
    printf("%s %d\n\n", "Hodil si:", cislo);
    return cislo;
}

int Hrac::vyberFigurku() {
    printf("%s", "Vyber figurku >> ");
    int idFigurky;
    cin >> idFigurky;

    while ((idFigurky - 1) > 3 || (idFigurky - 1) < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        printf("%s", "<Figurka neexistuje> \n");
        printf("%s", "Vyber figurku >> ");
        cin >> idFigurky;
    }

    return idFigurky;
}

void Hrac::overPozicieFigurok(int pocetKrokov, int id) {
    id--;
    int pocitadlo = 1;
    int pocetNaHP;
    int *povodnaPozicia = new int[2];
    int *ocakavanaPozicia = new int[2];

    while (pocitadlo != 0) {
        pocitadlo = 0;
        pocetNaHP = 0;
        povodnaPozicia[0] = figurky[id].getPoziciu()[0];
        povodnaPozicia[1] = figurky[id].getPoziciu()[1];


        if ((figurky[id].getPocetKrokov() + pocetKrokov) > 43) {       //po 39 krokoch je figurka pred domcekom (domcek - > 40, 41, 42, 43)
            printf("%s %c%d %s", "Figurka ",farbaHraca,id + 1," sa nemoze sa pohnut do domceka.\n");
            pocitadlo++;
        } else {
            figurky[id].posunOPolicka(pocetKrokov);
        }

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
                if (figurky[i].getJeNaHracejPloche()) {
                    pocetNaHP++;
                }
            }
        }
        if (pocitadlo > 0) {
            if (pocetNaHP == 0) {
                if (pocetKrokov != 6 && !dostupnaVZakladni()) {
                    printf("%s", "<Nemozno vykonat ziadny tah> \n");
                    break;
                } else {
                    id = vyberFigurku();
                    id = skontrolujCiJeNaHP(id) - 1;
                }
            } else {
                printf("%s", "<S danou figurkou sa nemozno pohnut> \n");
                id = vyberFigurku();
                id = skontrolujCiJeNaHP(id) - 1;
            }
        }
    }

}

bool Hrac::getVyhralHru() {
    if (pocetFigurokDomcek == 4)
        return true;
    return false;
}

void Hrac::setFigurkeZakladnu(int id) {
    figurky[id].setJeVZakladni();
}

bool Hrac::dostupnaVZakladni() {
    int pocet = 0;
    for (int i = 0; i < pocetFigurok; ++i) {
        if (figurky[i].getJeVZakladni()) {
            pocet++;
        }
    }
    if (pocet > 0) {
        return true;
    }
    return false;
}


