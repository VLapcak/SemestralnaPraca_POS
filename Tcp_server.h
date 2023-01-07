#ifndef SEMESTRALKA_LAPCAK_IHRING_TCP_SERVER_H
#define SEMESTRALKA_LAPCAK_IHRING_TCP_SERVER_H


class Tcp_server {
    int create_server(int argc, char *argv[]);
    static void *hrajServer(void *args);

public:
    Tcp_server(int argc, char *argv[]);

};


#endif //SEMESTRALKA_LAPCAK_IHRING_TCP_SERVER_H
