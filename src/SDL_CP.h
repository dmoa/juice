#pragma once

#include <stdio.h>

// SDL cross platform includes
#include <SDL2/SDL.h>

#ifdef _WIN32
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#else
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#endif

typedef int64_t  s64;
typedef int32_t  s32;
typedef int16_t  s16;
typedef int8_t   s8;
typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t  u8;

// For libraries that use printf
// (printf is disabled in SDL_Log for stupid reasons)
#define printf SDL_Log

inline u32 GetMouseDown(int i) { return SDL_GetMouseState(NULL, NULL) == SDL_BUTTON(i); };

// Render copy the entire texture
inline void RenderCopyWhole(SDL_Renderer* r, SDL_Texture* t, SDL_Rect* rt) { SDL_RenderCopy(r, t, NULL, rt); };

#define PI 3.14159265