#pragma once

#include <stdlib.h>
#include <time.h>

#include "../Globals/Window.h"

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

inline void GetMouseGameState(int* x, int* y) {
    SDL_GetMouseState(x, y);
    if (x) *x = *x / g_window.scale + g_window.gameplay_viewport.x;
    if (y) *y = *y / g_window.scale + g_window.gameplay_viewport.y;
}