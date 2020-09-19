#pragma once

#include <math.h>

inline float pyth(float x, float y, float x2, float y2) {
    return sqrt((x-x2)*(x-x2) + (y-y2)*(y-y2));
};