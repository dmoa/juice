#pragma once

#include <Engine/Engine.h>

struct Window {

    Window();
    void Clear();
    void SetDrawGameplay();
    void SetDrawOther();
    void Present();
    void Shutdown();

    SDL_Texture* gameplay_texture;
    SDL_Texture* other_texture;
    SDL_Rect other_texture_rect;
    SDL_Window* window;
    SDL_Surface* icon;
};