#pragma once

#include <Engine/Engine.h>

struct Crosshair {

    void LoadAsset();
    void DestroyAsset();
    void Draw();
    void Update();

    SDL_Texture* texture;
    SDL_Rect render_rect;
};