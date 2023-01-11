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

using namespace std;

void * Tcp_server::hrajServer(void *args) {


}

int Tcp_server::create_server(int argc, char **argv) {

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
    int clientSocket = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientAddressLength);

    //uzavretie pasivneho socketu <unistd.h>
    close(serverSocket);
    if (clientSocket < 0) {
        perror("Chyba - accept.");
    }

    char buffer[256];
    //const char* msg;
    string s;

    do {

        bzero(buffer, 256);
        //recv(clientSocket, buffer, sizeof(buffer), 0);
        hod(buffer, clientSocket);



        /*//cin >> s;
        fgets(buffer, 255, stdin);
        //msg = s.c_str();
        send(clientSocket, buffer, sizeof(buffer), 0);
        //printf("OK send\n");
        bzero(&buffer, 256);
        recv(clientSocket, &buffer, sizeof(buffer), 0);
        //printf("OK recv\n");
        printf("%s\n", buffer);*/

    } while (strcmp(buffer, "end") != 0);
    /*soketKlienta = clientSocket;


    //inicializacia dat zdielanych medzi vlaknami
    Manazer manazer = Manazer();
    pthread_mutex_t mut;
    pthread_cond_t sCond;
    pthread_cond_t kCond;
    pthread_mutex_init(&mut, nullptr);
    pthread_cond_init(&sCond, nullptr);
    pthread_cond_init(&kCond, nullptr);

    data d{
            manazer, 0, 0, 1, &mut, &sCond, &kCond
    };

    send(clientSocket, &d, sizeof(struct data), 0);

    //vytvorenie vlakna pre zapisovanie dat do socketu <pthread.h>
    pthread_t thread;
    pthread_create(&thread, nullptr, hrajServer, &d);


    pthread_join(thread, nullptr);

    //pockame na skoncenie zapisovacieho vlakna <pthread.h>

    pthread_mutex_destroy(&mut);
    pthread_cond_destroy(&sCond);
    pthread_cond_destroy(&kCond);*/

    //uzavretie socketu <unistd.h>
    close(clientSocket);

    return (EXIT_SUCCESS);
}

Tcp_server::Tcp_server(int argc, char **argv) {
    create_server(argc, argv);
}

void Tcp_server::overenieVstupu(char *buffer, int socket) {
/*    int cislo = 0;
    int idFigurky = 0;


    if (!suFigurkyNaHP()) {
        //Hrac hadze maximalne 3x dovtedy kym nehodi 6
        //ak hodi 6 tak sa postavi na startovaciu poziciu a hadze znovu
        int pocetHodov = 3;
        while (pocetHodov > 0) {
            cislo = hod();
            //cislo = 6;
            //cout << "HODIL som 6" << endl;
            if (cislo == 6) {
                //idFigurky = vyberFigurku();
                while (cislo == 6) {
                    idFigurky = vyberFigurku();
                    bool validnyTah = false;

                    while (!validnyTah) {
                        int pocitadlo = 0;
                        if (figurky[idFigurky - 1].getJeVZakladni()) {
                            for (int i = 0; i < pocetFigurok; ++i) {
                                if (i != idFigurky - 1) {
                                    if (figurky[i].getJeNaStartovacejPozicii()) {
                                        pocitadlo++;
                                    }
                                }
                            }
                            if (pocitadlo > 0) {
                                printf("%s", "<S danou figurkou sa nemozno pohnut> \n");
                                idFigurky = vyberFigurku();
                            } else {
                                figurky[idFigurky - 1].setNaStartovaciuPoziciu();
                                validnyTah = true;
                            }
                        } else if (figurky[idFigurky - 1].getJeNaStartovacejPozicii() ||
                                   figurky[idFigurky - 1].getJeNaHracejPloche()) {
                            overPozicieFigurok(cislo, idFigurky);
                            validnyTah = true;
                        } else if (figurky[idFigurky - 1].getJeVDomceku()) {
                            printf("%s", "<Figurka sa nemoze pohnut z domceka> \n");
                            idFigurky = vyberFigurku();
                        }
                    }
                    cislo = hod();

                    pocetHodov = 0;
                }
                idFigurky = vyberFigurku();
                idFigurky = skontrolujCiJeNaHP(idFigurky);
                figurky[idFigurky - 1].posunOPolicka(cislo);
            }
            pocetHodov--;
        }
    } else { //ak je uz nejaka figurka na hracej ploche

        // ak je nejaka figurka na SP tak tam ina nemoze ist
        cislo = hod();
        if (cislo == 6) {
            //idFigurky = vyberFigurku();
            while (cislo == 6) {
                bool validnyTah = false;
                idFigurky = vyberFigurku();
                while (!validnyTah) {
                    int pocitadlo = 0;
                    if (figurky[idFigurky - 1].getJeVZakladni()) {
                        for (int i = 0; i < pocetFigurok; ++i) {
                            if (i != idFigurky - 1) {
                                if (figurky[i].getJeNaStartovacejPozicii()) {
                                    pocitadlo++;
                                }
                            }
                        }
                        if (pocitadlo > 0) {
                            printf("%s", "<S danou figurkou sa nemozno pohnut> \n");
                            idFigurky = vyberFigurku();
                        } else {
                            figurky[idFigurky - 1].setNaStartovaciuPoziciu();
                            validnyTah = true;
                        }

                    } else if (figurky[idFigurky - 1].getJeNaStartovacejPozicii() ||
                               figurky[idFigurky - 1].getJeNaHracejPloche()) {
                        overPozicieFigurok(cislo, idFigurky);
                        validnyTah = true;
                    } else if (figurky[idFigurky - 1].getJeVDomceku()) {
                        printf("%s", "<Figurka sa nemoze pohnut z domceka> \n");
                        idFigurky = vyberFigurku();
                    }
                }
                cislo = hod();
            }
            idFigurky = vyberFigurku();
            idFigurky = skontrolujCiJeNaHP(idFigurky);
            overPozicieFigurok(cislo, idFigurky);
        } else {
            idFigurky = vyberFigurku();
            idFigurky = skontrolujCiJeNaHP(idFigurky);
            overPozicieFigurok(cislo, idFigurky);
        }

    }
    pocetFigurokDomcek = 0;
    for (int i = 0; i < pocetFigurok; ++i) {
        if (figurky[i].getJeVDomceku()) {
            pocetFigurokDomcek++;
        }
    }*/
}

int Tcp_server::hod(char *buffer, int socket) {
    //printf("%s", "Hod kockou >> ");
    const char* msg = "Hod kockou >> ";
    send(socket, msg, strlen(msg) + 1, 0);
    bzero(buffer, 256);
    recv(socket, buffer, sizeof(buffer), 0);
    while (strcmp(buffer, "hod") == 0) {
        bzero(buffer, 256);
        msg = "<Nespravny prikaz>\n Hod kockou >> ";
        send(socket, msg, strlen(msg) + 1, 0);


        recv(socket, buffer, sizeof(buffer), 0);

        printf("%s\n", buffer);
    }

    bzero(buffer, 256);
    int cislo = kocka.getCislo();
    string s = "Hodil si: " + to_string(cislo);
    msg = s.c_str();
    send(socket, msg, strlen(msg) + 1, 0);
    return cislo;
}

