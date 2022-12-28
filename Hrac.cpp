#include "Hrac.h"
#include <iostream>

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

    figurky[1].setJeNaStartovacejPozicii(true);
    //if je Hrac na tahu

    int cislo = 0;
    int idFigurky = 0;
    if (hracoveFigurkySuVDomcekuAleboVZakladni()) {
        //Hrac hadze maximalne 3x dovtedy kym nehodi 6
        //ak hodi 6 tak sa postavi na startovaciu poziciu a hadze znovu
        for (int pocetHodov = 0; pocetHodov < 1; pocetHodov++) {

                cislo = hod();
                while (cislo == 6) {
                    idFigurky = vyberFigurku();
                    // posun zo zakladne na startovaciu poziciu
                    if (hracoveFigurkySuVDomcekuAleboVZakladni()) {
                        figurky[idFigurky - 1].setPoziciu(figurky[idFigurky - 1].getStartovaciePozicie(farbaHraca)[0],figurky[idFigurky - 1].getStartovaciePozicie(farbaHraca)[1]);
                        figurky[idFigurky - 1].setJeNaStartovacejPozicii(true);
                        figurky[idFigurky - 1].setJeVZakladni(false);
                    } else if (figurky[idFigurky - 1].getJeNaStartovacejPozicii()) {

                    }

                    cislo = hod();
                }
                idFigurky = vyberFigurku();

                break;
        }


    } else {

        cislo = hod();


        //TODO: ak hodi 6 Hrac si vyberie, s ktorou figurkou sa pohne

        //TODO: ak hodi 6 hodi znovu

    } /*else {

            //TODO: vyberie, s ktorou figurkou sa pohne

        }*/

}



bool Hrac::hracoveFigurkySuVDomcekuAleboVZakladni() {
    if ((getFigurka(0).getJeVZakladni() || getFigurka(0).getJeVDomceku()) &&
        (getFigurka(1).getJeVZakladni() || getFigurka(1).getJeVDomceku()) &&
        (getFigurka(2).getJeVZakladni() || getFigurka(2).getJeVDomceku()) &&
        (getFigurka(3).getJeVZakladni() || getFigurka(3).getJeVDomceku())) {
        return true;
    }
    return false;
}

/*void Hrac::hod() {

    int cislo = 0;
    cout << ">>";
    string hod;
    cin >> hod;
    if (hod == "hod") {
        cislo = kocka.getCislo();
        cout << "Hodil si: " << cislo << endl;
    }
    int idFigurky = vyberFigurku();
    // pohni figurkou o cislo


    while (cislo == 6) {

        cout << ">>";
        cin >> hod;
        if (hod == "hod") {
            cislo = kocka.getCislo();
            cout << "Hodil si: " << cislo << endl;
        }
        vyberFigurku();
    }


}*/

int Hrac::hod() {
    int cislo = 0;
    cout << ">>";
    string hod;
    cin >> hod;
    if (hod == "hod") {
        cislo = kocka.getCislo();
        cout << "Hodil si: " << cislo << endl;
    }
    return cislo;
}

/*int Hrac::vyberFigurku() {
    cout << "Vyber figurku >>";
    int idFigurky;
    cin >> idFigurky;
    figurky[idFigurky-1].setJeNaStartovacejPozicii(true);
    figurky[idFigurky-1].setJeVZakladni(false);
    return idFigurky;
}*/

int Hrac::vyberFigurku() {
    cout << "Vyber figurku >>";
    int idFigurky;
    cin >> idFigurky;
    return idFigurky;
}

