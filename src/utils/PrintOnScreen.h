#pragma once

#include <SDL_CP.h>

struct PrintOnScreen {
    SDL_Rect rect = {5, 0, 50, 50};
    SDL_Texture* fps_texture = NULL;
    void Draw(std::string text, int x, int y) {
        rect.x = x; rect.y = y;
        fps_texture = Text::CreateTexture(text);
        SDL_QueryTexture(fps_texture, NULL, NULL, & rect.w, & rect.h);
        SDL_RenderCopy(g_window.rdr, fps_texture, NULL, & rect);
        SDL_DestroyTexture(fps_texture);
    }
};