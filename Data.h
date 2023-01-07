//
// Created by Adrián on 7. 1. 2023.
//

#ifndef SEMESTRALKA_LAPCAK_IHRING_DATA_H
#define SEMESTRALKA_LAPCAK_IHRING_DATA_H


#include "Manazer.h"
#include "pthread.h"

class Data {
public:
    Manazer manazer;
    /*int socket;
    char* userName;*/
    int aktualneId;
    int idServer;
    int idKlient;
    pthread_mutex_t *mutex;
    pthread_cond_t *condServer;
    pthread_cond_t *condKlient;




#endif //SEMESTRALKA_LAPCAK_IHRING_DATA_H
