#pragma once

#include <SDL_CP.h>
#include "Text.h"

void PrintScreen(std::string text, int x, int y) {
    SDL_Rect rect = {x, y, 50, 50};
    SDL_Texture* fps_texture = NULL;
    fps_texture = Text::CreateTexture(text);
    RenderCopyWhole(g_window.rdr, fps_texture, & rect);
    SDL_DestroyTexture(fps_texture);
};