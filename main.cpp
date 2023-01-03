#include <iostream>
#include <cstdlib>
#include "Tcp_server.h"
#include "Manazer.h"

using namespace std;


int main(int argc, char *argv[]) {

    srand(time(nullptr));

    Tcp_server tcpServer = Tcp_server(argc, argv);

    //Manazer manazer = Manazer();

    return 0;

}
