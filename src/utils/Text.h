#pragma once

#include <string>

#include <Engine/Engine.h>

struct Text {
    static void LoadFont();
    static void DestroyFont();
    static SDL_Texture* CreateTexture(std::string text);
    static TTF_Font* main_font;
    static SDL_Color white_color;
};