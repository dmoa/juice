// Engine is built on top of SDL.
// SDL functions have prefix SDL_.....
// Engine functions don't have a prefix.

#pragma once

#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <string>

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

// Printf + SDL do not work (something to do with SDL redirecting entry point, I think),
// and so you are forced to use SDL_Log. I've added a cheat here so that it's more readable.
// If I could avoid it I would.

// This also means if I ever figure out how to actually use printf, I can smoothly transition
// by doing something like #define print as printf + "\n"

#undef print
#undef printf

#define print SDL_Log
// for any libraries so that I don't have to replace all the printfs with print / SDL_Log.
#define printf SDL_Log

#ifdef _WIN32
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#else
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#endif

#include "Window.h"
#include "Graphics.h"
#include "Text.h"
#include "Controls.h"
#include "Asset.h"
#include "Clock.h"
#include "Animation.h"
#include "ExtraMath.h"

inline void EngineInit() {
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    srand(time(0));
    g_text.LoadFont();
    g_controls.Init();
}

inline void EngineQuit() {
    g_text.DestroyFont();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}