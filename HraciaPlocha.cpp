#include "HraciaPlocha.h"
#include "Hrac.h"
#include <iostream>

using namespace std;


HraciaPlocha::HraciaPlocha(Hrac *h) {
    for (int i = 0; i < 4; ++i) {
        hraci[i] = h[i];
    }
}

//// funkcia pre vykreslenie hracej plochy
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
                    aktualnaPlocha[figurka.getPoziciu()[0]][figurka.getPoziciu()[1]] = 5 * 10 + figurka.getIDFigurky();
                    break;
                case 'M':
                    aktualnaPlocha[figurka.getPoziciu()[0]][figurka.getPoziciu()[1]] = 6 * 10 + figurka.getIDFigurky();
                    break;
                case 'Z':
                    aktualnaPlocha[figurka.getPoziciu()[0]][figurka.getPoziciu()[1]] = 7 * 10 + figurka.getIDFigurky();
                    break;
                case 'B':
                    aktualnaPlocha[figurka.getPoziciu()[0]][figurka.getPoziciu()[1]] = 8 * 10 + figurka.getIDFigurky();
                    break;
            }
        }
    }
    cout << endl;

    // vypise textovy format cisel v poli reprezentujucich figurky a policka
    for (int i = 0; i < velkost; ++i) {

        for (int j = 0; j < velkost; ++j) {
            if (aktualnaPlocha[j][i] == 1)
                printf("%s", "[  ]");
            else if (aktualnaPlocha[j][i] == 2 || aktualnaPlocha[j][i] == 3)
                printf("%s", "(  )");

            else if (aktualnaPlocha[j][i] > 50 && aktualnaPlocha[j][i] < 60)
                printf("%s%d%s", "(C", aktualnaPlocha[j][i] % 50, ")");
            else if (aktualnaPlocha[j][i] > 60 && aktualnaPlocha[j][i] < 70)
                printf("%s%d%s", "(M", aktualnaPlocha[j][i] % 60, ")");
            else if (aktualnaPlocha[j][i] > 70 && aktualnaPlocha[j][i] < 80)
                printf("%s%d%s", "(Z", aktualnaPlocha[j][i] % 70, ")");
            else if (aktualnaPlocha[j][i] > 80 && aktualnaPlocha[j][i] < 90)
                printf("%s%d%s", "(B", aktualnaPlocha[j][i] % 80, ")");
            else
                printf("%s", "    ");
        }
        printf("\n");
    }
}

bool HraciaPlocha::getStatus() {
    return false;
}

//// funkcia pre nastavenie zakladnej hracej plochy
void HraciaPlocha::setZakladnaPlocha() {
    for (auto hr: hraci) {
        for (int j = 0; j < 4; ++j) {

            Figurka figurka = hr.getFigurka(j);
            switch (hr.getFarbu()) {
                case 'C':
                    figurka.setPoziciu(zBodyCerveny[j][0], zBodyCerveny[j][1]);
                    break;
                case 'M':
                    figurka.setPoziciu(zBodyModry[j][0], zBodyModry[j][1]);
                    break;
                case 'Z':
                    figurka.setPoziciu(zBodyZeleny[j][0], zBodyZeleny[j][1]);
                    break;
                case 'B':
                    figurka.setPoziciu(zBodyBiely[j][0], zBodyBiely[j][1]);
                    break;
            }
        }
    }
}


