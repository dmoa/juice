#pragma once

#include "sdl.h"

#include "Globals/Window.h"

struct Window {

    Window();
    void Clear();
    void SetDrawGameplay();
    void SetDrawOther();
    void Present(SDL_Rect* gameplay_viewport);
    void Shutdown();

    SDL_Texture* gameplay_texture;
    SDL_Texture* other_texture;
    SDL_Rect other_texture_rect;
    SDL_Window* window;
    SDL_Surface* icon;
};