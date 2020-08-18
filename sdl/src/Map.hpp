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
    int tiles_wide = 40;
    int tiles_high = 40;

    std::vector<int> tiles;
    SDL_Texture* texture;
    SDL_Texture* saved_drawn_data = SDL_CreateTexture(global_window_data.rdr, NULL, SDL_TEXTUREACCESS_TARGET, 640, 640);
    SDL_Rect map_position_quad = {0, 0, global_window_data.w / global_window_data.scale, 100};
    SDL_Rect map_rendering_quad = {0, 0, global_window_data.w / global_window_data.scale, global_window_data.h / global_window_data.scale};
};