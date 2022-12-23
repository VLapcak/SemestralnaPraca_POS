#include "figurka.h"
#include "iostream"

figurka::figurka() {

    poziciaXY = new int[2];
    farbaFigurky = 'X';
    jeNaHracejPloche = false;
    jeVDomceku = false;

}

void figurka::posunOPolicka(int pocet) {

    for (int i = 0; i < pocet; ++i) {

       if (poziciaXY[0] == 4 && poziciaXY[1] <= 4)
       {
           poziciaXY[1]--;
       }
       else
           poziciaXY[0]++;
    }
}

void figurka::setFarbu(char farba) {
    farbaFigurky = farba;
}

void figurka::setPoziciu(int x, int y) {
    poziciaXY[0] = x;
    poziciaXY[1] = y;
}

int *figurka::getPoziciu() {

    return poziciaXY;
}




