#pragma once

#include "SDL2/SDL_rect.h"

struct Camera {
public:
    void UpdateViewport(int x, int y, int w, int h);
    SDL_Rect* GetViewport();
private:
    SDL_Rect viewport;
};