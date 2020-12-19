#pragma once

#include <SDL_CP.h>

struct GlobalWindowData {
    int w;
    int h;
    int scale;
    SDL_Renderer* rdr;
    int pixel_format;
};

extern GlobalWindowData g_window;