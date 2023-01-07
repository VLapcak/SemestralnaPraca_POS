#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <netdb.h>
#include "Tcp_server.h"
#include "Manazer.h"
#include "ZdielaneData.h"

int soketKlienta;

void * Tcp_server::hrajServer(void *args) {

    data *d = (data *) args;
    data *buffer;

    pthread_mutex_lock(d->mutex);
    do {
        pthread_mutex_unlock(d->mutex);
        pthread_mutex_lock(d->mutex);
        while (d->aktualneId != 0) {
            printf("Server caka na klienta\n");
            pthread_cond_wait(d->condServer, d->mutex);
        }
        int id = d->idServer;
        d->manazer.getHraci()[id].vykonajTah();
        d->manazer.skontrolujFigurky(id);
        d->manazer.getHraciaPlocha().vykresliPlochu();
        printf("prehadzujem na klienta\n");
        d->aktualneId = d->manazer.getDalsiHrac(d->aktualneId, 2);
        pthread_cond_signal(d->condKlient);

        buffer = d;
        send(soketKlienta, &buffer, sizeof(&buffer), 0);
        recv(soketKlienta, &d, sizeof(&d), 0);
        pthread_mutex_unlock(d->mutex);

        pthread_mutex_lock(d->mutex);
    } while (d->manazer.beziHra());
    pthread_mutex_unlock(d->mutex);

    pthread_exit(nullptr);
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
    soketKlienta = clientSocket;


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
    pthread_cond_destroy(&kCond);

    //uzavretie socketu <unistd.h>
    close(clientSocket);

    return (EXIT_SUCCESS);
}

Tcp_server::Tcp_server(int argc, char **argv) {
    create_server(argc, argv);
}

