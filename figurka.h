#pragma once
#ifndef SEMESTRALKA_LAPCAK_IHRING_PLAYER_H
#define SEMESTRALKA_LAPCAK_IHRING_PLAYER_H


class figurka {


private:
    int* poziciaXY;
    char farbaFigurky;
    bool jeNaHracejPloche; // je na hracej ploche inak je v startovacom mieste
    bool jeVDomceku; // koncova pozicia je domcek

public:
    figurka();
    void posunOPolicka(int pocet);
    void setFarbu(char farba);
    int* getPoziciu();
    void setPoziciu(int x, int y);
};


#endif //SEMESTRALKA_LAPCAK_IHRING_PLAYER_H
