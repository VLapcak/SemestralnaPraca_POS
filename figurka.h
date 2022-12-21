#pragma once
#ifndef SEMESTRALKA_LAPCAK_IHRING_PLAYER_H
#define SEMESTRALKA_LAPCAK_IHRING_PLAYER_H


class player {

    int poziciaX;
    int poziciaY;
    bool jeNaHracejPloche; // je na hracej ploche inak je v startovacom mieste
    bool jeVDomceku; // koncova pozicia je domcek

public:
    player(int x, int y);

};


#endif //SEMESTRALKA_LAPCAK_IHRING_PLAYER_H
