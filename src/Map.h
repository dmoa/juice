#pragma once

#include <vector>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <algorithm>
#include <map>

#include "sdl.h"

#include "utils/min.h"
#include "utils/max.h"
#include "utils/pyth_s.h"
#include "utils/random.h"
#include "utils/AABB.h"
#include "utils/SOARects.h"
#include "utils/LoadImage.h"

#include "Globals/All.h"

struct Player;
struct ECS;

struct Map {

    void LoadTexture();
    void ReloadTilesetTexture();
    void GivePlayerDeltaECS(Player* _player, float* _dt, ECS* _ecs);
    void CreateMapTexture();
    void CreateCollisionBoxes();
    std::vector<SDL_Rect>* GetCollisionBoxes() { return & collision_boxes; }
    int GetMapWidth () { return tiles_wide * tile_length; };
    int GetMapHeight() { return tiles_high * tile_length; };
    void DrawBase();
    void DrawObject(int id);
    void Update();
    void DestroyTextures();

    const int tile_length = 16;
    const int tiles_wide  = 48;
    const int tiles_high  = 48;
    const int map_width   = tile_length * tiles_wide;
    const int map_height  = tile_length * tiles_high;


    float* dt;
    Player* player;
    ECS* ecs;

    const int opacity_distance = 50; // minimum distance from player before objects become transparent
    std::map<int, float> object_opacities;

    std::vector<SDL_Rect> collision_boxes;


    int AddEntityIfPossible(int x, int y, ENTITY_NAME name);

    SDL_Texture* static_saved_drawn_data = SDL_CreateTexture(global_window_data.rdr, NULL, SDL_TEXTUREACCESS_TARGET, tiles_wide * tile_length, tiles_high * tile_length);
    SDL_Texture* texture;
};