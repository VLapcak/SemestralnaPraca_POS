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

using namespace std;

#define VELKOSTBUFFERA 1024

void *Tcp_server::hrajServer(void *args) {

    return nullptr;
}

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
    close(serverSocket);


    // vytvorit vlakna klientov


    char buffer[VELKOSTBUFFERA];
    bzero(buffer, VELKOSTBUFFERA);
    string s;
    idAktualnehoHraca = 0;
    string akutualnaPlocha = manazer.getPlocha();

    posliSpravu(akutualnaPlocha, clientSockets[idAktualnehoHraca]);
    prijmiSpravu(buffer, clientSockets[idAktualnehoHraca]);


    do {
        overenieVstupu(buffer, clientSockets[idAktualnehoHraca], idAktualnehoHraca);

        akutualnaPlocha = manazer.getPlocha();
        posliSpravu(akutualnaPlocha, clientSockets[idAktualnehoHraca]);
        idAktualnehoHraca++;
        if (idAktualnehoHraca == pocetKlientov)
            idAktualnehoHraca = 0;

    } while (strcmp(buffer, "end") != 0);


    for (int i = 0; i < 4; ++i) {
        close(clientSockets[i]);
    }


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

