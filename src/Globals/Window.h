#pragma once

#include <SDL2/SDL.h>

struct GlobalWindowData {
    int w;
    int h;
    int scale;
    SDL_Renderer* rdr;
    int pixel_format;
};

extern GlobalWindowData global_window_data;