#include "HraciaPlocha.h"
#include "Hrac.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;


HraciaPlocha::HraciaPlocha(Hrac *h) {
    velkost = 11;

    for (int i = 0; i < 4; ++i) {
        hraci[i] = h[i];
    }
}

void HraciaPlocha::vykresliPlochu() {


    //inicializacia aktualnej plochy aby sa rovnala zakladnej ploche
    for (int i = 0; i < velkost; ++i) {
        for (int j = 0; j < velkost; ++j) {
            aktualnaPlocha[i][j] = zakladnaPlocha[i][j];
        }
    }


    //dostan pozicie figurok a farby
    for (auto hr: hraci) {
        for (int j = 0; j < 4; ++j) {

            Figurka figurka = hr.getFigurka(j);
            switch (hr.getFarbu()) {
                case 'C':
                    //TODO startovacia pocizia
                    if (figurka.getJeNaStartovacejPozicii())
                        hr.getFigurka(j).setPoziciu(sBodCerveny[0], sBodCerveny[1]);
                    else
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
            if (aktualnaPlocha[j][i] == 1)
                cout << "[  ]";
            else if (aktualnaPlocha[j][i] == 2 || aktualnaPlocha[j][i] == 3)
                cout << "(  )";

            else if (aktualnaPlocha[j][i] > 50 && aktualnaPlocha[j][i] < 60)
                cout << "(C" << aktualnaPlocha[j][i] % 50 << ")";
            else if (aktualnaPlocha[j][i] > 60 && aktualnaPlocha[j][i] < 70)
                cout << "(M" << aktualnaPlocha[j][i] % 60 << ")";
            else if (aktualnaPlocha[j][i] > 70 && aktualnaPlocha[j][i] < 80)
                cout << "(Z" << aktualnaPlocha[j][i] % 70 << ")";
            else if (aktualnaPlocha[j][i] > 80 && aktualnaPlocha[j][i] < 90)
                cout << "(B" << aktualnaPlocha[j][i] % 80 << ")";
            else
                cout << "    ";
        }
        cout << endl;
    }

}

bool HraciaPlocha::getStatus() {
    return false;
}


