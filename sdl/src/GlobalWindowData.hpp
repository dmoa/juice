#pragma once

#include <SDL2/SDL.h>

struct GlobalWindowData {
    int w;
    int h;
    SDL_Renderer* rdr;
    const Uint8* keys_down;
};

extern GlobalWindowData global_window_data;