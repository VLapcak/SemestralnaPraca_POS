#ifndef SEMESTRALKA_LAPCAK_IHRING_TCP_SERVER_H
#define SEMESTRALKA_LAPCAK_IHRING_TCP_SERVER_H

#include <string>

using namespace std;

class Tcp_server {
    int create_server(int argc, char *argv[]);
    void* hrajHru(void* args);

public:
    Tcp_server(int argc, char *argv[]);
    static char* citaj(char* buffer, int newsockfd);
    static void zapis(char* buffer, int newsockfd);
};


#endif //SEMESTRALKA_LAPCAK_IHRING_TCP_SERVER_H
