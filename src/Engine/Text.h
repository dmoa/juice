#pragma once

#include <string>

#include "Window.h"

struct Text {
    static void LoadFont();
    static void DestroyFont();
    static SDL_Texture* CreateTexture(std::string text);
    static TTF_Font* main_font;
    static SDL_Color white_color;
};

#ifdef ENGINE_IMPLEMENTATION

SDL_Color Text::white_color = {255, 255, 255};
TTF_Font* Text::main_font = NULL;

void Text::LoadFont() {
    main_font = TTF_OpenFont("assets/font.ttf", 10);
    if (!main_font) SDL_Log("can't load font"); else SDL_Log("Font loaded.");
}

void Text::DestroyFont() {
    TTF_CloseFont(main_font);
}

SDL_Texture* Text::CreateTexture(std::string text) {
    SDL_Surface* temp_surface = TTF_RenderText_Solid(main_font, text.c_str(), white_color);
    if (!temp_surface) SDL_Log("failed to create surface\n");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(g_window.rdr, temp_surface);

    SDL_FreeSurface(temp_surface);

    return texture;
}

#endif