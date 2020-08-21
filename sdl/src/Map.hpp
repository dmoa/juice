#pragma once

#include <vector>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "GlobalWindowData.hpp"
#include "AABB.hpp"
#include "CollisionBoxes.hpp"

class Map {
public:
    void LoadTexture();
    void CreateMapTexture();
    void CreateCollisionBoxes();
    CollisionBoxes* GetCollisionBoxes() { return & collision_boxes; }
    int GetMapWidth () { return tiles_wide * tile_length; };
    int GetMapHeight() { return tiles_high * tile_length; };
    void Draw();
    void DestroyTextures();
private:
    const int tile_length = 16;
    const int tiles_wide = 48;
    const int tiles_high = 48;

    CollisionBoxes collision_boxes;

    std::vector<int> tiles;
    SDL_Texture* texture;
    SDL_Texture* saved_drawn_data = SDL_CreateTexture(global_window_data.rdr, NULL, SDL_TEXTUREACCESS_TARGET, tiles_wide * tile_length, tiles_high * tile_length);
};