#include "Manazer.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

Manazer::Manazer() {
    pocetHracov = 4;
    pocetPripojenychHracov = 0;
    idAktualnehoHraca = 0;

    for (int i = 0; i < pocetHracov; ++i) {
        hraci[i] = *new Hrac();
        hraci[i].setFarbu(farby[i]);
    }
    hp.setHracov(hraci);
    hp.setZakladnaPlocha();
    hp.vykresliPlochu();

    ////Pre test viacerych hracov - NEMAZAT!!!
    //vyberNahodnehoZacinajuceho();



}

typedef struct {
    int aktualneId;
    pthread_mutex_t *mutex;
    pthread_cond_t *condServer;
    pthread_cond_t *condKlient;
} DATA;
typedef struct {
    int id;
    DATA *data;
} SD;
typedef struct {
    int id;
    DATA *data;
} KD;

//id servera je 0
//id klienta je 1

void *Manazer::hrajKlient(void *args) {

    KD *klientData = (KD *) args;
    DATA *d = (DATA *) klientData->data;

    hp.vykresliPlochu();
    while (beziHra()) {

        pthread_mutex_lock(d->mutex);
        while (d->aktualneId != 1) {
            printf("Klient caka na server");
            pthread_cond_wait(d->condKlient, d->mutex);
        }
        int id = klientData->id;
        hraci[id].vykonajTah();
        skontrolujFigurky(id);
        hp.vykresliPlochu();
        printf("prehadzujem na server");
        d->aktualneId = 0;
        pthread_cond_signal(d->condServer);
        pthread_mutex_unlock(d->mutex);



    }

    pthread_exit(nullptr);
}

void *Manazer::hraj(void *args) {

    SD *serverData = (SD *) args;
    DATA *d = (DATA *) serverData->data;

    while (beziHra()) {
        pthread_mutex_lock(d->mutex);
        while (d->aktualneId != 0) {
            printf("Server caka na klienta");
            pthread_cond_wait(d->condServer, d->mutex);
        }
        int id = serverData->id;
        hraci[id].vykonajTah();
        skontrolujFigurky(id);
        hp.vykresliPlochu();
        printf("prehadzujem na klienta");
        d->aktualneId = 1;
        pthread_cond_signal(d->condKlient);
        pthread_mutex_unlock(d->mutex);

    }

    pthread_exit(nullptr);
}


bool Manazer::beziHra() {
    for (int i = 0; i < pocetHracov; ++i) {
        if (hraci[i].getVyhralHru()) {
            printf("%s\n", "---Hra sa skoncila---");
            printf("%s %c %s", "---Vyhral", farby[i], "hrac---");
            return false;
        }
    }
    return true;
}

void Manazer::dalsiHrac(int aktualneID) {
    if (aktualneID < pocetHracov - 1)
        aktualneID++;
    else
        aktualneID = 0;

    printf("\n%s %c %s", "-------------Na rade je", hraci[aktualneID].getFarbu(), "hrac-------------- \n");

}

void Manazer::vyberNahodnehoZacinajuceho() {
    idAktualnehoHraca = rand() % 3 + 0;
}

void Manazer::skontrolujFigurky(int id) {

    for (int f = 0; f < 4; ++f) {
        if (hraci[id].getFigurka(f).getJeNaHracejPloche()) { // figurky aktualne iduceho hraca

            for (int i = 0; i < pocetHracov; ++i) {
                for (int j = 0; j < 4; ++j) { // nepriatelske figurky

                    if (i != id) {
                        // aktualny hrac na tahu        v porovnani s ostatnymi hracmi a ich figurkami
                        if (hraci[id].getFigurka(f).getPoziciu()[0] ==
                            hraci[i].getFigurka(j).getPoziciu()[0]
                            && hraci[id].getFigurka(f).getPoziciu()[1] ==
                               hraci[i].getFigurka(j).getPoziciu()[1]) {

                            hraci[i].setFigurkeZakladnu(j);
                            setFigurkuNaZakladnu(farby[i], j);
                            printf("%c%d %s %c%d", farby[id], f + 1, "vyhodil", farby[i], j + 1);
                        }
                    }
                }
            }
        }
    }
}


void Manazer::setFigurkuNaZakladnu(char farba, int idFigurky) {
    int *pozicia = hp.getPoziciuZakladne(farba, idFigurky);
    switch (farba) {
        case 'C':
            hraci[0].getFigurka(idFigurky).setPoziciu(pozicia[0], pozicia[1]);
            break;
        case 'M':
            hraci[1].getFigurka(idFigurky).setPoziciu(pozicia[0], pozicia[1]);
            break;
        case 'B':
            hraci[2].getFigurka(idFigurky).setPoziciu(pozicia[0], pozicia[1]);
            break;
        case 'Z':
            hraci[3].getFigurka(idFigurky).setPoziciu(pozicia[0], pozicia[1]);
            break;

        default:
            printf("<Error, zle zadana farba>");
            break;
    }
}


void *Manazer::run_server(void *ptr) {
    {
        static_cast<Manazer *>(ptr)->hraj(ptr);
        return nullptr;
    }
}
void *Manazer::run_klient(void *ptr) {
    {
        static_cast<Manazer *>(ptr)->hrajKlient(ptr);
        return nullptr;
    }
}





