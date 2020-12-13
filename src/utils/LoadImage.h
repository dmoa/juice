#pragma once

#include <string>

#include "../sdl.h"
#include "int.h"
#include "../Globals/Window.h"
#include "ase_loader.h"

inline SDL_Texture* LoadImage(SDL_Renderer* renderer, std::string path) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, path.c_str());
    if (!texture) SDL_Log("%s%s", path.c_str(), " not found");
    return texture;
}

static SDL_Texture* LoadAse(SDL_Renderer* renderer, std::string file_path) {
    Ase_Output output = AseLoad(file_path);

    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, 100, 100, 8, SDL_PIXELFORMAT_INDEX8);
    if (! surface) SDL_Log("Surface could not be created!, %s\n", SDL_GetError());

//    ((SDL_Color*)surface->format->palette->colors)[1] = {255, 0, 0, 255};
    SDL_Color r = {255, 0, 0, 0};
    SDL_SetPaletteColors(surface->format->palette, & r, 0, 1);
    for (int i = 0; i < 100; i ++) {
        ((u8*)surface->pixels)[i] = 0;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(global_window_data.rdr, surface);
    if (! texture) SDL_Log("Texture could not be created!, %s\n", file_path.c_str());



    return texture;
}