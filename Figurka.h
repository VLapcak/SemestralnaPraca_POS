#pragma once
#ifndef SEMESTRALKA_LAPCAK_IHRING_PLAYER_H
#define SEMESTRALKA_LAPCAK_IHRING_PLAYER_H


class Figurka {


private:
    int* poziciaXY;
    char farbaFigurky;
    int idFigurky;
    bool jeVZakladni; // startovaci domcek
    bool naStartovacejPozicii; // Figurka bola v zakladni a Hrac hodil 6
    bool jeNaHracejPloche; // je na hracej ploche
    bool jeVDomceku; // presiel celou hracou plochu a dorazil na koncovu poziciu
    int startovaciePozicie[4][2] { {0,4}, {6,0}, {10,6}, {4,10} }; // startovacia pozicia figurky na zaklade farby a indexu
    int pocetKrokov; // kolko policok presla figurka na hracej ploche

public:
    Figurka();
    void posunOPolicka(int pocet);
    void setFarbu(char farba);
    void setPoziciu(int x, int y);
    void setJeNaHracejPloche(bool stav);
    void setJeNaStartovacejPozicii(bool stav);
    void setJeVDomceku(bool stav);
    void setJeVZakladni(bool stav);
    void setIDFigurky(int cislo);
    void setNaStartovaciuPoziciu();
    void odpocitajKroky(int pocet);

    int* getPoziciu();
    bool getJeVZakladni();
    bool getJeNaStartovacejPozicii();
    bool getJeNaHracejPloche();
    bool getJeVDomceku();
    int getIDFigurky();

};


#endif //SEMESTRALKA_LAPCAK_IHRING_PLAYER_H
