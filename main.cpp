#include <iostream>
//#include <SDL2/SDL.h>
#include "HraciaPlocha.h"


int main(int argc, char* argv[]) {

    srand(time(NULL));

    HraciaPlocha hp;
    hp.vykresliPlochu(11);
    hp.vykresliPlochu(11);
    hp.vykresliPlochu(11);

    return 0;

}
