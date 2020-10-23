#pragma once

#include <string>

#include "../sdl.h"

#include "../Globals/All.h"

struct Text {
public:
    static void LoadFont();
    static void DestroyFont();
    static SDL_Texture* CreateTexture(std::string text);
private:
    static TTF_Font* main_font;
    static SDL_Color white_color;
};