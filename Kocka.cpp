#include "Kocka.h"
#include <cstdlib>

int Kocka::getCislo() {
    return rand() % 6 + 1;
}