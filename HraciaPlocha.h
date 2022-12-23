#ifndef SEMESTRALKA_LAPCAK_IHRING_HRACIAPLOCHA_H
#define SEMESTRALKA_LAPCAK_IHRING_HRACIAPLOCHA_H


#include "hrac.h"

class HraciaPlocha {

private:
    int velkost;
    int pocetHracov;
    hrac hraci[4];
    char farby[4]{'C', 'M', 'Z', 'B'};

    // kde sa nachadzaju figurky na zaciatku hry
    int zBodyCerveny[4][2]{{0, 0},
                           {1, 0},
                           {0, 1},
                           {1,1}};

    int zBodyModry[4][2]{{9, 0},
                         {10, 0},
                         {9, 1},
                         {10,1}};

    int zBodyZeleny[4][2]{{0, 9},
                          {1, 9},
                          {0, 10},
                          {1,10}};

    int zBodyBiely[4][2]{{9, 9},
                         {10, 9},
                         {9, 10},
                         {10,10}};


    int zakladnaPlocha[11][11]{{2, 2, 0, 0, 1, 1, 1, 0, 0, 2, 2},
                               {2, 2, 0, 0, 1, 3, 1, 0, 0, 2, 2},
                               {0, 0, 0, 0, 1, 3, 1, 0, 0, 0, 0},
                               {0, 0, 0, 0, 1, 3, 1, 0, 0, 0, 0},
                               {1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1},
                               {1, 3, 3, 3, 3, 0, 3, 3, 3, 3, 1},
                               {1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1},
                               {0, 0, 0, 0, 1, 3, 1, 0, 0, 0, 0},
                               {0, 0, 0, 0, 1, 3, 1, 0, 0, 0, 0},
                               {2, 2, 0, 0, 1, 3, 1, 0, 0, 2, 2},
                               {2, 2, 0, 0, 1, 1, 1, 0, 0, 2, 2}};

    int aktualnaPlocha[11][11]{0};



public:
    HraciaPlocha();
    void vykresliPlochu();
    bool getStatus();
};


#endif //SEMESTRALKA_LAPCAK_IHRING_HRACIAPLOCHA_H