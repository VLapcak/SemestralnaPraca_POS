#include "HraciaPlocha.h"
#include "Hrac.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;


HraciaPlocha::HraciaPlocha(Hrac* h) {
    velkost = 11;

    for (int i = 0; i < 4; ++i) {
        hraci[i] = h[i];
    }
}

void HraciaPlocha::vykresliPlochu() {

    //                      [x,y]
    //cerveny zacina na     [4,0]
    //zeleny zacina na      [0,6]
    //biely zacina na       [6,10]
    //modry zacina na       [10,4]


    //inicializacia aktualnej plochy aby sa rovnala zakladnej ploche
    for (int i = 0; i < velkost; ++i) {
        for (int j = 0; j < velkost; ++j) {
            aktualnaPlocha[i][j] = zakladnaPlocha[i][j];
        }
    }


    //dostan pozicie figurok a farby
    for (auto hr: hraci) {
        for (int j = 0; j < 4; ++j) {

            switch (hr.getFarbu()) {
                case 'C':
                    hr.getFigurka(j).setPoziciu(zBodyCerveny[j][0], zBodyCerveny[j][1]);
                    aktualnaPlocha[hr.getFigurka(j).getPoziciu()[0]][hr.getFigurka(j).getPoziciu()[1]] =
                            5 * 10 + hr.getFigurka(j).getIDFigurky();
                    break;
                case 'M':
                    hr.getFigurka(j).setPoziciu(zBodyModry[j][0], zBodyModry[j][1]);
                    aktualnaPlocha[hr.getFigurka(j).getPoziciu()[0]][hr.getFigurka(j).getPoziciu()[1]] =
                            6 * 10 + hr.getFigurka(j).getIDFigurky();
                    break;
                case 'Z':
                    hr.getFigurka(j).setPoziciu(zBodyZeleny[j][0], zBodyZeleny[j][1]);
                    aktualnaPlocha[hr.getFigurka(j).getPoziciu()[0]][hr.getFigurka(j).getPoziciu()[1]] =
                            7 * 10 + hr.getFigurka(j).getIDFigurky();
                    break;
                case 'B':
                    hr.getFigurka(j).setPoziciu(zBodyBiely[j][0], zBodyBiely[j][1]);
                    aktualnaPlocha[hr.getFigurka(j).getPoziciu()[0]][hr.getFigurka(j).getPoziciu()[1]] =
                            8 * 10 + hr.getFigurka(j).getIDFigurky();
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
                cout << "[  ]";
            else if (aktualnaPlocha[i][j] == 2 || aktualnaPlocha[i][j] == 3)
                cout << "(  )";

            else if (aktualnaPlocha[i][j] > 50 && aktualnaPlocha[i][j] < 60)
                cout << "(C" << aktualnaPlocha[i][j] % 50 << ")";
            else if (aktualnaPlocha[i][j] > 60 && aktualnaPlocha[i][j] < 70)
                cout << "(M" << aktualnaPlocha[i][j] % 60 << ")";
            else if (aktualnaPlocha[i][j] > 70 && aktualnaPlocha[i][j] < 80)
                cout << "(Z" << aktualnaPlocha[i][j] % 70 << ")";
            else if (aktualnaPlocha[i][j] > 80 && aktualnaPlocha[i][j] < 90)
                cout << "(B" << aktualnaPlocha[i][j] % 80 << ")";
            else
                cout << "    ";
        }
        cout << endl;
    }

}

bool HraciaPlocha::getStatus() {
    return false;
}


