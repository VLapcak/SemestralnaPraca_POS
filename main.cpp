#include <iostream>
#include <cstdlib>
//#include <SDL2/SDL.h>
#include "HraciaPlocha.h"

using namespace std;


int main(int argc, char* argv[]) {

    srand(time(nullptr));

    HraciaPlocha hp = HraciaPlocha();
    Kocka kocka = Kocka();

    hp.vykresliPlochu();

    //hod kockou napisany cez konzolu
    string hod;
    cin >> hod;

    if (hod == "Hod") {
        cout << "Hodil si: " << kocka.getCislo() << endl;
    }



    return 0;

}
