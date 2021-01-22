#pragma once

#include <stdlib.h>
#include <time.h>

#define PI 3.14159265

inline float pyth_s(float x, float y, float x2, float y2) {
    return (x-x2)*(x-x2) + (y-y2)*(y-y2);
}

inline int random(int min, int max) {
    return rand() % (max - min) + min;
}

inline float min(float a, float b) {
    if (b < a) return b;
    return a;
}

inline float max(float a, float b) {
    if (b > a) return b;
    return a;
}

inline bool AABB(float x, float y, float w, float h, float x2, float y2, float w2, float h2) {
    return x + w > x2 && x < x2 + w2 && y + h > y2 && y < y2 + h2;
}