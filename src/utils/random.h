#pragma once

#include <stdlib.h>
#include <time.h>

inline int random(int min, int max) {
    return rand() % (max - min) + min;
}