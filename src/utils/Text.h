#pragma once

#include <string>

#include <SDL_CP.h>

#include "../Globals/All.h"

struct Text {
    static void LoadFont();
    static void DestroyFont();
    static SDL_Texture* CreateTexture(std::string text);
    static TTF_Font* main_font;
    static SDL_Color white_color;
};