#pragma once

#include <Engine/Engine.h>

struct Crosshair {

    void LoadAsset();
    void DestroyAsset();
    void Draw();
    void Update();

    SDL_Texture* texture;
    SDL_Rect render_rect = {100, 100, -1, -1};
    float x;
    float y;
    float controller_crosshair_v = 300;
};