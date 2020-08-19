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

// #include "Player.hpp"

class Map {
public:
    // void GivePlayer(Pl);
    void LoadTexture();
    void CreateMapTexture();
    void CreateCollisionBoxes();
    CollisionBoxes* GetCollisionBoxes();
    void Draw();
    void DestroyTextures();
private:
    // Player* player;

    const int tile_length = 16;
    const int tiles_wide = 40;
    const int tiles_high = 40;

    CollisionBoxes collision_boxes;

    std::vector<int> tiles;
    SDL_Texture* texture;
    SDL_Texture* saved_drawn_data = SDL_CreateTexture(global_window_data.rdr, NULL, SDL_TEXTUREACCESS_TARGET, 640, 640);
    SDL_Rect map_position_quad = {0, 0, global_window_data.w / global_window_data.scale, 100};
    SDL_Rect map_rendering_quad = {0, 0, global_window_data.w / global_window_data.scale, global_window_data.h / global_window_data.scale};
};