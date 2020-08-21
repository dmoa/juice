#pragma once

#include "SDL2/SDL_rect.h"

struct Camera {
public:
    void ChangePosX(float x);
    void ChangePosY(float y);
    void UpdateSize(int w, int h);
    SDL_Rect* GetViewport();
private:
    SDL_Rect viewport = {0, 0, 0, 0};
    float real_x = 0;
    float real_y = 0;
};