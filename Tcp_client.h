#ifndef SEMESTRALKA_LAPCAK_IHRING_TCP_CLIENT_H
#define SEMESTRALKA_LAPCAK_IHRING_TCP_CLIENT_H

class Tcp_client {
    int create_client(int argc, char *argv[]);

public:
    Tcp_client(int argc, char *argv[]);
    static char* citaj(char *buffer, int newsockfd);
    static void zapis(char *buffer, int newsockfd);
};

#endif //SEMESTRALKA_LAPCAK_IHRING_TCP_CLIENT_H
