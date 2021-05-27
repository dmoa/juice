#pragma once

#include <stdlib.h>
#include <time.h>

#define PI 3.14159265
#define ROOT2 1.41421356237

inline float pyth_s(float x, float y, float x2, float y2) {
    return (x-x2)*(x-x2) + (y-y2)*(y-y2);
}

inline float pyth(float a, float b) {
    return sqrt(a*a + b*b);
}

// min inclusive, max exclusive.
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

inline int abs(int n) {
    return (n<0) ? -n : n;
}

inline bool AABB(float x, float y, float w, float h, float x2, float y2, float w2, float h2) {
    return x + w > x2 && x < x2 + w2 && y + h > y2 && y < y2 + h2;
}

inline bool AABB(Asset_Ase* a, Asset_Ase* b, float x, float y, float x2, float y2) {
    return x + a->damage_box->x + a->damage_box->w > x2 + b->damage_box->x && x + a->damage_box->x < x2 + b->damage_box->x + b->damage_box->w && y + a->damage_box->y + a->damage_box->h > y2 + b->damage_box->y && y + a->damage_box->y < y2 + b->damage_box->y + b->damage_box->h;
}