#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "GlobalWindowData.hpp"

class Window {
public:
    Window();
    void Clear();
    void SetDrawGameplay();
    void SetDrawOther();
    void Present(SDL_Rect* gameplay_viewport);
    void Shutdown();
private:
    SDL_Texture* gameplay_texture;
    SDL_Texture* other_texture;
    SDL_Rect other_texture_rect;
    SDL_Window* window;
    SDL_Surface* icon;
};