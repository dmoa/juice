#include "random.hpp"

int random(int min, int max) {
    return rand() % (max - min) + min;
}