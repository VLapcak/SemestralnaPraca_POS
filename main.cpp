#include <iostream>
#include <cstdlib>
//#include <SDL2/SDL.h>
#include "HraciaPlocha.h"
#include "Manazer.h"

using namespace std;


int main(int argc, char* argv[]) {

    srand(time(nullptr));

    Manazer manazer = Manazer();
    Kocka kocka = Kocka();


    //hod kockou napisany cez konzolu
    cout << ">>";
    string hod;
    cin >> hod;

    if (hod == "Hod") {
        cout << "Hodil si: " << kocka.getCislo() << endl;
    }



    return 0;

}
