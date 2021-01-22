#pragma once

#include <stdio.h>
#include <stdint.h>

typedef int64_t  s64;
typedef int32_t  s32;
typedef int16_t  s16;
typedef int8_t   s8;
typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t  u8;

// SDL cross platform includes
#include <SDL2/SDL.h>

#ifdef _WIN32
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#else
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#endif

struct GlobalWindowData {
    int w;
    int h;
    int scale;
    SDL_Renderer* rdr;
    SDL_Rect gameplay_viewport;
};
extern GlobalWindowData g_window;

// The following are functions that revolve around SDL, usually small changes that make life easier.

inline void GetMouseGameState(int* x, int* y) {
    SDL_GetMouseState(x, y);
    if (x) *x = *x / g_window.scale + g_window.gameplay_viewport.x;
    if (y) *y = *y / g_window.scale + g_window.gameplay_viewport.y;
}

inline u32 GetMouseDown(int i) { return SDL_GetMouseState(NULL, NULL) == SDL_BUTTON(i); };

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