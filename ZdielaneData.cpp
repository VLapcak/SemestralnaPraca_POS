//
// Created by Adrián on 6. 1. 2023.
//

#include <cstring>
#include "ZdielaneData.h"
#include "Manazer.h"


void ZdielaneData::dataInit(DATA *data, const char* userName, int socket) {
    data->socket = socket;
    data->userName[6] = '\0';
    data->aktualneId = 0;
    data->idServer = 0;
    data->idKlient = 1;
    strncpy(data->userName, userName, 6);
    pthread_mutex_init(data->mutex, nullptr);
    pthread_cond_init(data->condServer, nullptr);
    pthread_cond_init(data->condKlient, nullptr);
}

