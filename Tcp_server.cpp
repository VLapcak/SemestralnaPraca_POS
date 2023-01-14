#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <netdb.h>
#include "Manazer.h"
#include "Kocka.h"
#include <iostream>
#include <limits>
#include <utility>


using namespace std;

#define VELKOSTBUFFERA 1024

Hrac* hraci[4];

Kocka kocka;
int idAktualnehoHraca;

typedef struct data {
    Manazer manazer;
    int *socket;
    //struct sockaddr_in;
    int idAktualnehoHraca;
    char* buffer;
    int pocetPripojenychKlientov;

    pthread_mutex_t* mutex;
    pthread_cond_t* cond_klient;
}DATA;

typedef struct dataKlient {
    int id;

    DATA *data;
}DATAKLIENT;



void posliSpravu(string sprava, int socket) {
    send(socket, sprava.c_str(), strlen(sprava.c_str()) + 1, 0);

}

void prijmiSpravu(char *buffer, int socket) {
    bzero(buffer, VELKOSTBUFFERA);
    recv(socket, buffer, VELKOSTBUFFERA, 0);
    printf("%s\n", buffer);
}


int hod(char *buffer, int socket) {
    posliSpravu("Hod kockou >> ", socket);

    prijmiSpravu(buffer, socket);

    string bufferString;
    for (int i = 0; i < 4; ++i) {
        bufferString += buffer[i];
    }
    while (bufferString != "hod\n") {
        posliSpravu("<Nespravny prikaz>\nHod kockou >> ", socket);
        bufferString = "";
        prijmiSpravu(buffer, socket);
        for (int i = 0; i < 4; ++i) {
            bufferString += buffer[i];
        }
    }
    int cislo = kocka.getCislo();
    string s = "Hodil si: " + to_string(cislo);
    posliSpravu(s, socket);
    return cislo;
}



int vyberFigurku(char *buffer, int socket) {
    posliSpravu("Vyber figurku >> ", socket);
    int idFigurky;
    prijmiSpravu(buffer, socket);
    idFigurky = atoi(buffer);
    printf("figurka s id %d (%s)\n", idFigurky, buffer);

    while ((idFigurky - 1) > 3 || (idFigurky - 1) < 0) {
        posliSpravu("<Figurka neexistuje> \nVyber figurku >> ", socket);
        prijmiSpravu(buffer, socket);
        idFigurky = atoi(buffer);
        printf("figurka s id %d (%s)\n", idFigurky, buffer);
    }

    return idFigurky;
}


int skontrolujCiJeNaHP(int idFigurky, char* buffer, int socket) {
    while (!hraci[idAktualnehoHraca]->getFigurka(idFigurky - 1).getJeNaHracejPloche()) {
        posliSpravu("<Figurka nie je na hracej ploche!> \n", socket);
        idFigurky = vyberFigurku(buffer, socket);
    }
    return idFigurky;
}

/*
void overPozicieFigurok(int pocetKrokov, int id) {
    id--;
    int pocitadlo = 1;
    int pocetNaHP;
    int *povodnaPozicia = new int[2];
    int *ocakavanaPozicia = new int[2];

    while (pocitadlo != 0) {
        pocitadlo = 0;
        pocetNaHP = 0;
        povodnaPozicia[0] = figurky[id].getPoziciu()[0];
        povodnaPozicia[1] = figurky[id].getPoziciu()[1];


        if ((figurky[id].getPocetKrokov() + pocetKrokov) > 43) {       //po 39 krokoch je figurka pred domcekom (domcek - > 40, 41, 42, 43)
            printf("%s %c%d %s", "Figurka ",farbaHraca,id + 1," sa nemoze sa pohnut do domceka.\n");
            pocitadlo++;
        } else {
            figurky[id].posunOPolicka(pocetKrokov);
        }

        ocakavanaPozicia[0] = figurky[id].getPoziciu()[0];
        ocakavanaPozicia[1] = figurky[id].getPoziciu()[1];

        for (int i = 0; i < pocetFigurok; ++i) {
            if (i != id) {
                if (ocakavanaPozicia[0] == figurky[i].getPoziciu()[0] &&
                    ocakavanaPozicia[1] == figurky[i].getPoziciu()[1]) {
                    figurky[id].odpocitajKroky(pocetKrokov);
                    figurky[id].setPoziciu(povodnaPozicia[0], povodnaPozicia[1]);
                    pocitadlo++;
                }
                if (figurky[i].getJeNaHracejPloche()) {
                    pocetNaHP++;
                }
            }
        }
        if (pocitadlo > 0) {
            if (pocetNaHP == 0) {
                if (pocetKrokov != 6 && !dostupnaVZakladni()) {
                    printf("%s", "<Nemozno vykonat ziadny tah> \n");
                    break;
                } else {
                    id = vyberFigurku();
                    id = skontrolujCiJeNaHP(id) - 1;
                }
            } else {
                printf("%s", "<S danou figurkou sa nemozno pohnut> \n");
                id = vyberFigurku();
                id = skontrolujCiJeNaHP(id) - 1;
            }
        }
    }

}
 */

void overenieVstupu(char *buffer, int socket, int idHraca) {
    int cislo = 0;
    int idFigurky = 0;

    Figurka* figurky[4];
    Figurka *f = hraci[idHraca]->getFigurky();
    for (int i = 0; i < 4; ++i) {
        figurky[i] = &f[i];
    }


    if (!hraci[idHraca]->suFigurkyNaHP()) {
        int pocetHodov = 3;
        while (pocetHodov > 0) {
            cislo = hod(buffer, socket);
            if (cislo == 6) {
                while (cislo == 6) {
                    idFigurky = vyberFigurku(buffer, socket);
                    bool validnyTah = false;

                    while (!validnyTah) {
                        int pocitadlo = 0;
                        if (figurky[idFigurky - 1]->getJeVZakladni()) {
                            for (int i = 0; i < 4; ++i) {
                                if (i != idFigurky - 1) {
                                    if (figurky[i]->getJeNaStartovacejPozicii()) {
                                        pocitadlo++;
                                    }
                                }
                            }
                            if (pocitadlo > 0) {
                                printf("%s", "<S danou figurkou sa nemozno pohnut> \n");
                                idFigurky = vyberFigurku(buffer, socket);
                            } else {
                                figurky[idFigurky - 1]->setNaStartovaciuPoziciu();
                                validnyTah = true;
                            }
                        } else if (figurky[idFigurky - 1]->getJeNaStartovacejPozicii() ||
                                   figurky[idFigurky - 1]->getJeNaHracejPloche()) {
                            hraci[idHraca]->overPozicieFigurok(cislo, idFigurky);
                            validnyTah = true;
                        } else if (figurky[idFigurky - 1]->getJeVDomceku()) {
                            printf("%s", "<Figurka sa nemoze pohnut z domceka> \n");
                            idFigurky = vyberFigurku(buffer, socket);
                        }
                    }
                    cislo = hod(buffer, socket);

                    pocetHodov = 0;
                }
                idFigurky = vyberFigurku(buffer, socket);
                idFigurky = skontrolujCiJeNaHP(idFigurky, buffer, socket);
                figurky[idFigurky - 1]->posunOPolicka(cislo);
            }
            pocetHodov--;
            printf("pokus %d", pocetHodov);
        }
    } else { //ak je uz nejaka figurka na hracej ploche

        // ak je nejaka figurka na SP tak tam ina nemoze ist
        cislo = hod(buffer, socket);
        if (cislo == 6) {
            //idFigurky = vyberFigurku();
            while (cislo == 6) {
                bool validnyTah = false;
                idFigurky = vyberFigurku(buffer, socket);
                while (!validnyTah) {
                    int pocitadlo = 0;
                    if (figurky[idFigurky - 1]->getJeVZakladni()) {
                        for (int i = 0; i < 4; ++i) {
                            if (i != idFigurky - 1) {
                                if (figurky[i]->getJeNaStartovacejPozicii()) {
                                    pocitadlo++;
                                }
                            }
                        }
                        if (pocitadlo > 0) {
                            posliSpravu("<S danou figurkou sa nemozno pohnut> \n", socket);
                            idFigurky = vyberFigurku(buffer, socket);
                        } else {
                            figurky[idFigurky - 1]->setNaStartovaciuPoziciu();
                            validnyTah = true;
                        }

                    } else if (figurky[idFigurky - 1]->getJeNaStartovacejPozicii() ||
                               figurky[idFigurky - 1]->getJeNaHracejPloche()) {
                        hraci[idHraca]->overPozicieFigurok(cislo, idFigurky);
                        validnyTah = true;
                    } else if (figurky[idFigurky - 1]->getJeVDomceku()) {
                        posliSpravu("<Figurka sa nemoze pohnut z domceka> \n", socket);
                        idFigurky = vyberFigurku(buffer, socket);
                    }
                }
                cislo = hod(buffer, socket);
            }
            idFigurky = vyberFigurku(buffer, socket);
            idFigurky = skontrolujCiJeNaHP(idFigurky, buffer, socket);
            hraci[idHraca]->overPozicieFigurok(cislo, idFigurky);
        } else {
            idFigurky = vyberFigurku(buffer, socket);
            idFigurky = skontrolujCiJeNaHP(idFigurky, buffer, socket);
            hraci[idHraca]->overPozicieFigurok(cislo, idFigurky);
        }

    }
    hraci[idHraca]->overPocetFigurokDomcek();
}

static void *obsluhaKlienta(void *args) {
    auto *dataklient = (DATAKLIENT *) args;
    /*
    pthread_mutex_lock(dataklient->data->mutex);
    while (dataklient->id != dataklient->data->idAktualnehoHraca) {
        posliSpravu("Nie si na ťahu! Čakaj, dokým neprídeš na rad.\n", dataklient->data->socket[dataklient->id]);
        pthread_cond_wait(dataklient->data->cond_klient, dataklient->data->mutex);
    }
    pthread_cond_broadcast(dataklient->data->cond_klient);
    pthread_mutex_unlock(dataklient->data->mutex);*/

    pthread_mutex_lock(dataklient->data->mutex);
    string akutualnaPlocha = dataklient->data->manazer.getPlocha();

    posliSpravu(akutualnaPlocha, dataklient->data->socket[dataklient->data->idAktualnehoHraca]);
    prijmiSpravu(dataklient->data->buffer, dataklient->data->socket[dataklient->data->idAktualnehoHraca]);

    string bufferString;
    for (int i = 0; i < 4; ++i) {
        bufferString += dataklient->data->buffer[i];
    }
    while (bufferString != "end\n") {
        pthread_mutex_unlock(dataklient->data->mutex);

        pthread_mutex_lock(dataklient->data->mutex);
        overenieVstupu(dataklient->data->buffer, dataklient->data->socket[dataklient->data->idAktualnehoHraca], dataklient->data->idAktualnehoHraca);

        akutualnaPlocha = dataklient->data->manazer.getPlocha();
        posliSpravu(akutualnaPlocha, dataklient->data->socket[dataklient->data->idAktualnehoHraca]);
        dataklient->data->idAktualnehoHraca++;
        if (dataklient->data->idAktualnehoHraca == dataklient->data->pocetPripojenychKlientov)
            dataklient->data->idAktualnehoHraca = 0;

        pthread_mutex_unlock(dataklient->data->mutex);

        pthread_mutex_lock(dataklient->data->mutex);
    }
    pthread_mutex_unlock(dataklient->data->mutex);

    pthread_exit(nullptr);
}

int main(int argc, char **argv) {

    if (argc < 3) {
        perror("Server je nutne spustit s nasledujucimi argumentmi: port pouzivatel.");
    }
    int port = atoi(argv[1]);
    if (port <= 0) {
        perror("Port musi byt cele cislo vacsie ako 0.");
    }
    char *userName = argv[2];

    //vytvorenie TCP socketu <sys/socket.h>
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        perror("Chyba - socket.");
    }

    //definovanie adresy servera <arpa/inet.h>
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;             //internetove sockety
    serverAddress.sin_addr.s_addr = INADDR_ANY;     //prijimanie spojenia z celeho internetu
    serverAddress.sin_port = htons(port);   //nastavenie portu

    //prepojenie adresy servera so socketom <sys/socket.h>
    if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
        perror("Chyba - bind.");
    }

    //server bude prijimat nove spojenia cez socket serverSocket <sys/socket.h>
    listen(serverSocket, 10);

    //server caka na pripojenie klienta <sys/socket.h>
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLength = sizeof(clientAddress);

    printf("Cakam na pripojenie hracov...\n");
    int pocetKlientov = 0;
    int maxKlientov = 1;
    int clientSockets[4]{0};
    while (pocetKlientov < maxKlientov) {
        int newClient = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientAddressLength);
        for (int i = 0; i < maxKlientov; ++i) {
            if (clientSockets[i] == 0) {
                clientSockets[i] = newClient;
                pocetKlientov++;
                break;
            }
        }
        //uzavretie pasivneho socketu <unistd.h>

        if (clientSockets[pocetKlientov] < 0) {
            perror("Chyba - accept.");
        }
        printf("Aktualny pocet hracov je %d z %d\n", pocetKlientov, maxKlientov);

    }
    //nastavenie Datovej struktury
    Manazer manazer = Manazer();
    Hrac *h = manazer.getHraci();
    for (int i = 0; i < 4; ++i) {
        hraci[i] = &h[i];
    }
    idAktualnehoHraca = 0;
    char buffer[VELKOSTBUFFERA];
    bzero(buffer, VELKOSTBUFFERA);
    pthread_mutex_t mutex;
    pthread_cond_t cond_klient;
    pthread_mutex_init(&mutex, nullptr);
    pthread_cond_init(&cond_klient, nullptr);

    DATA data = {manazer, clientSockets, idAktualnehoHraca, buffer, pocetKlientov, &mutex, &cond_klient};

    // vytvorit vlakna klientov
    pthread_t klientVlakno[pocetKlientov];
    DATAKLIENT dataklient[pocetKlientov];
    for (int i = 0; i < pocetKlientov; i++) {
        dataklient[i].id = i;
        dataklient[i].data = &data;
        dataklient[i].data->socket = &clientSockets[i];
        pthread_create(&klientVlakno[i], nullptr, obsluhaKlienta, &dataklient[i]);
    }

    for (int i = 0; i < pocetKlientov; ++i) {
        pthread_join(klientVlakno[i], nullptr);
    }

    for (int i = 0; i < pocetKlientov; ++i) {
        close(clientSockets[i]);
    }

    close(serverSocket);

    return (EXIT_SUCCESS);
}



