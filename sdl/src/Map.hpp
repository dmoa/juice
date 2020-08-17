#pragma once

#include <vector>
#include <stdlib.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "GlobalWindowData.hpp"

class Map {
public:
    void LoadTexture();
    void CreateMapTexture();
    void Draw();
    void DestroyTextures();
private:
    std::vector<int> tiles;
    SDL_Texture* texture;
    SDL_Texture* saved_drawn_data = SDL_CreateTexture(global_window_data.rdr, NULL, SDL_TEXTUREACCESS_TARGET, 640, 640);
    SDL_Rect iter_quad = {0, 0, 16, 16};
    SDL_Rect iter_pos  = {0, 0, 16 * global_window_data.scale, 16 * global_window_data.scale};
};