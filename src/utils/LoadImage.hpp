#pragma once

#include <string>

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

inline SDL_Texture* LoadImage(SDL_Renderer* renderer, std::string path) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, path.c_str());
    if (!texture) SDL_Log("%s%s",path.c_str(), " not found");
    return texture;
}