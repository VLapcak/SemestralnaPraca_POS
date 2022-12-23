#include "kocka.h"
#include "stdlib.h"

int kocka::getCislo() {
    return rand() % 6 + 1;
}