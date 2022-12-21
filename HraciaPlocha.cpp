#include "HraciaPlocha.h"
#include <iostream>
#include "stdlib.h"
#include "stdio.h"

using namespace std;

void HraciaPlocha::vykresliPlochu(int rozmer) {

    int pole[rozmer][rozmer] = {{5, 5, 0, 0, 1, 1, 1, 0, 0, 6, 6},
                                {5, 5, 0, 0, 1, 2, 1, 0, 0, 6, 6},
                                {0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0},
                                {0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0},
                                {1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1},
                                {1, 2, 2, 2, 2, 0, 2, 2, 2, 2, 1},
                                {1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1},
                                {0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0},
                                {0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0},
                                {8, 8, 0, 0, 1, 2, 1, 0, 0, 7, 7},
                                {8, 8, 0, 0, 1, 1, 1, 0, 0, 7, 7}};

    //                      [x,y]
    //cerveny zacina na     [4,0]
    //modry zacina na       [0,6]
    //zeleny zacina na      [11,6]
    //biely zacina na       [4,11]

    for (int i = 0; i < rozmer; ++i) {

        for (int j = 0; j < rozmer; ++j) {
            if (pole[i][j] == 1)
                cout << "[ ]";
            else if (pole[i][j] == 2)
                cout << "( )";
            else if (pole[i][j] == 5)
                cout << "(C)";
            else if (pole[i][j] == 6)
                cout << "(M)";
            else if (pole[i][j] == 7)
                cout << "(Z)";
            else if (pole[i][j] == 8)
                cout << "(B)";
            else
                cout << "   ";
        }
        cout << endl;
    }
    string hod;
    cin >> hod;

    if (hod == "Hod") {

        int cislo = rand() % 6 + 1;
        cout << "Hodil si: " << cislo << endl;
    }

}