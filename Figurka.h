#pragma once
#ifndef SEMESTRALKA_LAPCAK_IHRING_PLAYER_H
#define SEMESTRALKA_LAPCAK_IHRING_PLAYER_H


class Figurka {


private:
    int* poziciaXY;
    char farbaFigurky;
    bool jeVZakladni; // startovaci domcek
    bool jeNaStartovacejPozicii; // Figurka bola v zakladni a Hrac hodil 6
    bool jeNaHracejPloche; // je na hracej ploche
    bool jeVDomceku; // presiel celou hracou plochu a dorazil na koncovu poziciu


public:
    Figurka();
    void posunOPolicka(int pocet);
    void setFarbu(char farba);
    int* getPoziciu();
    void setPoziciu(int x, int y);
    bool getJeVZakladni();
    bool getJeNaStartovacejPozicii();
    bool getJeNaHracejPloche();
    bool getJeVDomceku();

};


#endif //SEMESTRALKA_LAPCAK_IHRING_PLAYER_H
