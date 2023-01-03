#include <iostream>
#include <cstdlib>
#include "Tcp_server.h"
#include "Tcp_client.h"
#include "Manazer.h"

using namespace std;


int main(int argc, char* argv[]) {


    printf(">> ");
    char s;
    cin >> s;
    srand(time(nullptr));


    if (s == 'k') {
        printf("vyberam si teba klient");
        Tcp_client tcpClient = Tcp_client(argc, argv);
    }
    else if(s == 's') {
        printf("vyberam si teba server");
        Tcp_server tcpServer = Tcp_server(argc, argv);
    }

    Manazer manazer = Manazer();

    return 0;

}
