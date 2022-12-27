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

    if (hadze3Krat()) {
        //Hrac hadze maximalne 3x dovtedy kym nehodi 6
        //ak hodi 6 tak sa postavi na startovaciu poziciu a hadze znovu
        for (int pocetHodov = 0; pocetHodov < 1; pocetHodov++) {

            hod();
            /*if (cislo == 6) {
                //vyloz panacika z domceku
                //ak je na startovacej pozicii zniz pocetFigurokStartovaciaPozicia

                cout << "Vyber figurku >>";
                int idFigurky;
                cin >> idFigurky;

                figurky[idFigurky].setJeNaStartovacejPozicii(true);
                figurky[idFigurky].setJeVZakladni(false);

                bool dohadzal = false;
                while (dohadzal)
                {
                    cout << "Vyber figurku >>";
                    int idFigurky;
                    cin >> idFigurky;
                }
                break;
                //TODO: ak hodi 6 hrac si vyberie, s ktorou figurkou sa pohne

                //TODO: ak hodi 6 hodi znovu
            }*/
        }


    } else {

        //Hrac hadze iba 1x

        int cislo = kocka.getCislo();
        if (cislo == 6) {

            //TODO: ak hodi 6 Hrac si vyberie, s ktorou figurkou sa pohne

            //TODO: ak hodi 6 hodi znovu

        } else {

            //TODO: vyberie, s ktorou figurkou sa pohne

        }

    }

}

bool Hrac::hadze3Krat() {
    if ((getFigurka(0).getJeVZakladni() || getFigurka(0).getJeVDomceku()) &&
        (getFigurka(1).getJeVZakladni() || getFigurka(1).getJeVDomceku()) &&
        (getFigurka(2).getJeVZakladni() || getFigurka(2).getJeVDomceku()) &&
        (getFigurka(3).getJeVZakladni() || getFigurka(3).getJeVDomceku())) {
        return true;
    }
    return false;
}

void Hrac::hod() {

    int cislo = 0;
    cout << ">>";
    string hod;
    cin >> hod;
    if (hod == "hod") {
        cislo = kocka.getCislo();
        cout << "Hodil si: " << cislo << endl;
    }
    vyberFigurku();

    while (cislo == 6) {

        cout << ">>";
        cin >> hod;
        if (hod == "hod") {
            cislo = kocka.getCislo();
            cout << "Hodil si: " << cislo << endl;
        }
        vyberFigurku();
    }


}

int Hrac::vyberFigurku() {
    cout << "Vyber figurku >>";
    int idFigurky;
    cin >> idFigurky;
    figurky[idFigurky-1].setJeNaStartovacejPozicii(true);
    figurky[idFigurky-1].setJeVZakladni(false);
    return idFigurky;
}


