#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <netdb.h>
#include "Tcp_server.h"
#include "Manazer.h"
#include "Kocka.h"
#include <iostream>
#include <limits>
#include <utility>


using namespace std;

#define VELKOSTBUFFERA 1024

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

void *Tcp_server::obsluhaKlienta(void *args) {
    DATAKLIENT *dataklient = (DATAKLIENT *) args;



    /*pthread_mutex_lock(dataklient->data->mutex);
    while (dataklient->id != dataklient->data->idAktualnehoHraca) {
        posliSpravu("Nie si na ťahu! Čakaj, dokým neprídeš na rad.\n", dataklient->data->socket[dataklient->id]);
        pthread_cond_wait(dataklient->data->cond_klient, dataklient->data->mutex);
    }
    pthread_cond_broadcast(dataklient->data->cond_klient);
    pthread_mutex_unlock(dataklient->data->mutex);*/


    string akutualnaPlocha = dataklient->data->manazer.getPlocha();

    posliSpravu(akutualnaPlocha, dataklient->data->socket[dataklient->data->idAktualnehoHraca]);
    prijmiSpravu(dataklient->data->buffer, dataklient->data->socket[dataklient->data->idAktualnehoHraca]);


    string bufferString;
    for (int i = 0; i < 4; ++i) {
        bufferString += dataklient->data->buffer[i];
    }
    while (bufferString != "end\n") {
        overenieVstupu(dataklient->data->buffer, dataklient->data->socket[dataklient->data->idAktualnehoHraca], dataklient->data->idAktualnehoHraca);

        akutualnaPlocha = dataklient->data->manazer.getPlocha();
        posliSpravu(akutualnaPlocha, dataklient->data->socket[dataklient->data->idAktualnehoHraca]);
        dataklient->data->idAktualnehoHraca++;
        if (dataklient->data->idAktualnehoHraca == dataklient->data->pocetPripojenychKlientov)
            dataklient->data->idAktualnehoHraca = 0;

    }

    pthread_exit(nullptr);
}

void * Tcp_server::execute()
{
    std::cout << "Task :: execute from Thread ID : " << pthread_self()
              << std::endl;
    return NULL;
}
void * Tcp_server::threadFunc(void *)
{
    std::cout << "Task :: threadFunc from Thread ID : " << pthread_self()
              << std::endl;
    return NULL;
}

typedef void * (*THREADFUNCPTR)(void *);

int Tcp_server::create_server(int argc, char **argv, Manazer manazer) {

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


    // vytvorit vlakno pre server
    pthread_t serverVlakno;
    //pthread_create(serverVlakno, nullptr, ,);


    int pocetKlientov = 0;
    int maxKlinetov = 2;
    int clientSockets[4]{0};
    while (pocetKlientov < maxKlinetov) {
         int newClient = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientAddressLength);
        for (int i = 0; i < maxKlinetov; ++i) {
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
        printf("Aktualny pocet hracov je %d z %d\n", pocetKlientov, maxKlinetov);

    }

    Tcp_server *taskPtr;
    taskPtr = new Tcp_server(argc, argv);

    //nastavenie Datovej struktury
    idAktualnehoHraca = 0;
    char buffer[VELKOSTBUFFERA];
    bzero(buffer, VELKOSTBUFFERA);
    pthread_mutex_t mutex;
    pthread_cond_t cond_klient;
    pthread_mutex_init(&mutex, nullptr);
    pthread_cond_init(&cond_klient, nullptr);

    DATA data = {std::move(manazer), clientSockets, idAktualnehoHraca, buffer, pocetKlientov, &mutex, &cond_klient};

    // vytvorit vlakna klientov
    pthread_t klientVlakno[pocetKlientov];
    DATAKLIENT dataklient[pocetKlientov];
    for (int i = 0; i < pocetKlientov; i++) {
        dataklient[i].id = i + 1;
        dataklient[i].data = &data;
        dataklient[i].data->socket = &clientSockets[i];
        //pthread_create(&klientVlakno[i], nullptr, obsluhaKlienta, &dataklient[i]);
        //thread_create(&klientVlakno[i], nullptr, (THREADFUNCPTR) Tcp_server::execute(), taskPtr);
        pthread_create(&klientVlakno[i], nullptr, (THREADFUNCPTR) Tcp_server::obsluhaKlienta(taskPtr), &dataklient[i]);
    }

    /*char buffer[VELKOSTBUFFERA];
    bzero(buffer, VELKOSTBUFFERA);*/
    /*string akutualnaPlocha = manazer.getPlocha();

    posliSpravu(akutualnaPlocha, clientSockets[idAktualnehoHraca]);
    prijmiSpravu(buffer, clientSockets[idAktualnehoHraca]);


    do {
        overenieVstupu(buffer, clientSockets[idAktualnehoHraca], idAktualnehoHraca);

        akutualnaPlocha = manazer.getPlocha();
        posliSpravu(akutualnaPlocha, clientSockets[idAktualnehoHraca]);
        idAktualnehoHraca++;
        if (idAktualnehoHraca == pocetKlientov)
            idAktualnehoHraca = 0;

    } while (strcmp(buffer, "end") != 0);*/

    for (int i = 0; i < 4; ++i) {
        pthread_join(clientSockets[i], nullptr);
    }

    for (int i = 0; i < 4; ++i) {
        close(clientSockets[i]);
    }

    close(serverSocket);

    return (EXIT_SUCCESS);
}

Tcp_server::Tcp_server(int argc, char **argv) {
    Manazer manazer = Manazer();
    Hrac *h = manazer.getHraci();
    for (int i = 0; i < 4; ++i) {
        hraci[i] = &h[i];
        //hraci[i]->setFarbu('F');
    }
    create_server(argc, argv, manazer);
}

void Tcp_server::overenieVstupu(char *buffer, int socket, int idHraca) {
    int cislo = 0;
    int idFigurky = 0;

    Figurka figurky[4];
    for (int i = 0; i < 4; ++i) {
        figurky[i] = hraci[idHraca]->getFigurka(i);
    }

    if (!hraci[idHraca]->suFigurkyNaHP()) {
        int pocetHodov = 3;
        while (pocetHodov > 0) {
            cislo = hod(buffer, socket);
            //cislo = 6;
            //cout << "HODIL som 6" << endl;
            if (cislo == 6) {
                while (cislo == 6) {
                    idFigurky = vyberFigurku(buffer, socket);
                    bool validnyTah = false;

                    while (!validnyTah) {
                        int pocitadlo = 0;
                        if (figurky[idFigurky - 1].getJeVZakladni()) {
                            for (int i = 0; i < 4; ++i) {
                                if (i != idFigurky - 1) {
                                    if (figurky[i].getJeNaStartovacejPozicii()) {
                                        pocitadlo++;
                                    }
                                }
                            }
                            if (pocitadlo > 0) {
                                printf("%s", "<S danou figurkou sa nemozno pohnut> \n");
                                idFigurky = vyberFigurku(buffer, socket);
                            } else {
                                figurky[idFigurky - 1].setNaStartovaciuPoziciu();
                                validnyTah = true;
                            }
                        } else if (figurky[idFigurky - 1].getJeNaStartovacejPozicii() ||
                                   figurky[idFigurky - 1].getJeNaHracejPloche()) {
                            hraci[idHraca]->overPozicieFigurok(cislo, idFigurky);
                            validnyTah = true;
                        } else if (figurky[idFigurky - 1].getJeVDomceku()) {
                            printf("%s", "<Figurka sa nemoze pohnut z domceka> \n");
                            idFigurky = vyberFigurku(buffer, socket);
                        }
                    }
                    cislo = hod(buffer, socket);

                    pocetHodov = 0;
                }
                idFigurky = vyberFigurku(buffer, socket);
                idFigurky = hraci[idHraca]->skontrolujCiJeNaHP(idFigurky);
                figurky[idFigurky - 1].posunOPolicka(cislo);
            }
            pocetHodov--;
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
                    if (figurky[idFigurky - 1].getJeVZakladni()) {
                        for (int i = 0; i < 4; ++i) {
                            if (i != idFigurky - 1) {
                                if (figurky[i].getJeNaStartovacejPozicii()) {
                                    pocitadlo++;
                                }
                            }
                        }
                        if (pocitadlo > 0) {
                            posliSpravu("<S danou figurkou sa nemozno pohnut> \n", socket);
                            idFigurky = vyberFigurku(buffer, socket);
                        } else {
                            figurky[idFigurky - 1].setNaStartovaciuPoziciu();
                            validnyTah = true;
                        }

                    } else if (figurky[idFigurky - 1].getJeNaStartovacejPozicii() ||
                               figurky[idFigurky - 1].getJeNaHracejPloche()) {
                        hraci[idHraca]->overPozicieFigurok(cislo, idFigurky);
                        validnyTah = true;
                    } else if (figurky[idFigurky - 1].getJeVDomceku()) {
                        posliSpravu("<Figurka sa nemoze pohnut z domceka> \n", socket);
                        idFigurky = vyberFigurku(buffer, socket);
                    }
                }
                cislo = hod(buffer, socket);
            }
            idFigurky = vyberFigurku(buffer, socket);
            idFigurky = hraci[idHraca]->skontrolujCiJeNaHP(idFigurky);
            hraci[idHraca]->overPozicieFigurok(cislo, idFigurky);
        } else {
            idFigurky = vyberFigurku(buffer, socket);
            idFigurky = hraci[idHraca]->skontrolujCiJeNaHP(idFigurky);
            hraci[idHraca]->overPozicieFigurok(cislo, idFigurky);
        }

    }
    hraci[idHraca]->overPocetFigurokDomcek();
}

int Tcp_server::hod(char *buffer, int socket) {
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

int Tcp_server::vyberFigurku(char *buffer, int socket) {
    posliSpravu("Vyber figurku >> ", socket);
    int idFigurky;
    prijmiSpravu(buffer, socket);
    idFigurky = atoi(buffer);

    while ((idFigurky - 1) > 3 || (idFigurky - 1) < 0) {
        //cin.clear();
        //cin.ignore(numeric_limits<streamsize>::max(), '\n');
        posliSpravu("<Figurka neexistuje> \nVyber figurku >> ", socket);
        prijmiSpravu(buffer, socket);
        idFigurky = atoi(buffer);
    }

    return idFigurky;
}

void Tcp_server::posliSpravu(string sprava, int socket) {
    send(socket, sprava.c_str(), strlen(sprava.c_str()) + 1, 0);

}

void Tcp_server::prijmiSpravu(char *buffer, int socket) {
    bzero(buffer, VELKOSTBUFFERA);
    recv(socket, buffer, VELKOSTBUFFERA, 0);
    printf("%s\n", buffer);
}



