#include "HraciaPlocha.h"
#include "Hrac.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;


HraciaPlocha::HraciaPlocha() {
    velkost = 11;
    pocetHracov = 4;

    for (int i = 0; i < pocetHracov; ++i) {
        hraci[i] = *new Hrac();
        hraci[i].setFarbu(farby[i]);
    }

    //aktualnaPlocha = new int[11][11];
    vykresliPlochu();

}

void HraciaPlocha::vykresliPlochu() {

    //                      [x,y]
    //cerveny zacina na     [4,0]
    //modry zacina na       [0,6]
    //zeleny zacina na      [11,6]
    //biely zacina na       [4,11]

    //inicializacia aktualnej plochy aby sa rovnala zakladnej ploche
    for (int i = 0; i < velkost; ++i) {
        for (int j = 0; j < velkost; ++j) {
            aktualnaPlocha[i][j] = zakladnaPlocha[i][j];
        }
    }


    //dostan pozicie figurok a farby
    for (auto hr : hraci) {
        for (int j = 0; j < 4; ++j) {

            switch (hr.getFarbu()) {
                case 'C': hr.getFigurka(j).setPoziciu(zBodyCerveny[j][0], zBodyCerveny[j][1]);
                    aktualnaPlocha[hr.getFigurka(j).getPoziciu()[0]][hr.getFigurka(j).getPoziciu()[1]] = 5;
                    break;
                case 'M': hr.getFigurka(j).setPoziciu(zBodyModry[j][0], zBodyModry[j][1]);
                    aktualnaPlocha[hr.getFigurka(j).getPoziciu()[0]][hr.getFigurka(j).getPoziciu()[1]] = 6;
                    break;
                case 'Z': hr.getFigurka(j).setPoziciu(zBodyZeleny[j][0], zBodyZeleny[j][1]);
                    aktualnaPlocha[hr.getFigurka(j).getPoziciu()[0]][hr.getFigurka(j).getPoziciu()[1]] = 7;
                    break;
                case 'B': hr.getFigurka(j).setPoziciu(zBodyBiely[j][0], zBodyBiely[j][1]);
                    aktualnaPlocha[hr.getFigurka(j).getPoziciu()[0]][hr.getFigurka(j).getPoziciu()[1]] = 8;
                    break;
            }

            //int* p = hr.getFigurka(j).getPoziciu();
            //aktualnaPlocha[p[0]][p[1]] = 5;
            //cout << hr.getFarbu() << "(" << p[0] << "x" << p[1] << ") ";


            //delete[] p;
        }

    }


    cout << endl;

    //preved cisla pola na textovu podobu
    for (int i = 0; i < velkost; ++i) {

        for (int j = 0; j < velkost; ++j) {
            if (aktualnaPlocha[i][j] == 1)
                cout << "[ ]";
            else if (aktualnaPlocha[i][j] == 2 || aktualnaPlocha[i][j] == 3)
                cout << "( )";

            else if (aktualnaPlocha[i][j] == 5)
                cout << "(C)";
            else if (aktualnaPlocha[i][j] == 6)
                cout << "(M)";
            else if (aktualnaPlocha[i][j] == 7)
                cout << "(Z)";
            else if (aktualnaPlocha[i][j] == 8)
                cout << "(B)";
            else
                cout << "   ";
        }
        cout << endl;
    }

    //hod kockou napisany cez konzolu
    string hod;
    cin >> hod;

    if (hod == "Hod") {

        int cislo = rand() % 6 + 1;
        cout << "Hodil si: " << cislo << endl;
    }

}

bool HraciaPlocha::getStatus() {
    return false;
}


