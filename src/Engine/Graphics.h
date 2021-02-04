#pragma once

#include "Text.h"
#include "Window.h"

// The following are functions that revolve around SDL, usually small changes that make life easier.

inline void GetTextureSize(SDL_Texture* t, int* w, int* h) { SDL_QueryTexture(t, NULL, NULL, w, h); };

enum DrawnFrom {
    TOP_LEFT,
    CENTER
};

// RenderCopyWhole renders the entire texture, no cropping.
// By default, it draws from the top left, but can specify to draw from center.
// The SDL_Rect* arg only has to contain x and y, width and height we figure out in the function.
inline void RenderCopyWhole(SDL_Renderer* r, SDL_Texture* t, SDL_Rect* _rt, DrawnFrom pos = TOP_LEFT) {

    SDL_Rect rt = *_rt;
    GetTextureSize(t, & rt.w, & rt.h);

    if (pos == CENTER) {
        rt.x -= rt.w / 2;
        rt.y -= rt.h / 2;
    }

    SDL_RenderCopy(r, t, NULL, & rt);
};

void PrintScreen(std::string text, int x, int y);

#ifdef ENGINE_IMPLEMENTATION

void PrintScreen(std::string text, int x, int y) {
    SDL_Rect rect = {x, y, -1, -1};
    SDL_Texture* fps_texture = NULL;
    fps_texture = g_text.CreateTexture(text);
    RenderCopyWhole(g_window.rdr, fps_texture, & rect);
    SDL_DestroyTexture(fps_texture);
};

#endif