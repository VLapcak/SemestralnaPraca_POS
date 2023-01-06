//
// Created by Adrián on 6. 1. 2023.
//

#ifndef SEMESTRALKA_LAPCAK_IHRING_ZDIELANEDATA_H
#define SEMESTRALKA_LAPCAK_IHRING_ZDIELANEDATA_H


#include "Manazer.h"

class ZdielaneData {
public:
    typedef struct {
        Manazer manazer;
        int socket;
        char* userName;
        int aktualneId;
        int idServer;
        int idKlient;
        pthread_mutex_t *mutex;
        pthread_cond_t *condServer;
        pthread_cond_t *condKlient;
    } DATA;
    /*typedef struct {
        int id;
        DATA *data;
    } SD;
    typedef struct {
        int id;
        DATA *data;
    } KD;*/

    void dataInit(DATA *data, const char* userName, int socket);
};


#endif //SEMESTRALKA_LAPCAK_IHRING_ZDIELANEDATA_H
