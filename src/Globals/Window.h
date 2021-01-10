#pragma once

#include <SDL_CP.h>

struct GlobalWindowData {
    int w;
    int h;
    int scale;
    SDL_Renderer* rdr;
    SDL_Rect gameplay_viewport;
};

extern GlobalWindowData g_window;