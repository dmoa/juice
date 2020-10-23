#pragma once

#include <SDL2/SDL.h>

struct GlobalWindowData {
    int w;
    int h;
    int scale;
    SDL_Renderer* rdr;
};

extern GlobalWindowData global_window_data;