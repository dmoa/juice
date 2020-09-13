#pragma once

#include <vector>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <algorithm>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "utils/min.hpp"
#include "utils/max.hpp"
#include "utils/pyth.hpp"
#include "utils/random.hpp"
#include "utils/AABB.hpp"
#include "utils/CollisionBoxes.hpp"

#include "GlobalWindowData.hpp"
#include "objects/SOAObjects.hpp"
#include "objects/ObjectsNames.hpp"
#include "objects/ObjectsInfo.hpp"
#include "objects/ObjectTypes.hpp"

class Player;
class DrawObjects;

class Map {
public:
    void LoadTexture();
    void ReloadTilesetTexture();
    void GivePlayerDeltaDrawObjects(Player* _player, float* _dt, DrawObjects* _draw_objects);
    void CreateMapTexture();
    void CreateCollisionBoxes();
    CollisionBoxes* GetCollisionBoxes() { return & collision_boxes; }
    int GetMapWidth () { return tiles_wide * tile_length; };
    int GetMapHeight() { return tiles_high * tile_length; };
    void DrawBase();
    void DrawObject(float x, float y, OBJECT_NAMES name, int id);
    void Update();
    void DestroyTextures();

    const int tile_length = 16;
    const int tiles_wide  = 48;
    const int tiles_high  = 48;
    const int map_width   = tile_length * tiles_wide;
    const int map_height  = tile_length * tiles_high;

    // Already know dimensions from OBJECTS_QUAD_DIMENSIONS, so no need to use widths and heights.
    const SOARects STATIC_QUADS_INFO = {
        {0, 16, 32, 32},
        {32, 32, 32, 48},
        {},{},
    };

private:
    float* dt;
    Player* player;
    DrawObjects* draw_objects;

    const int opacity_distance = 50; // minimum distance from player before objects become transparent
    std::map<int, float> object_opacities;

    CollisionBoxes collision_boxes;


    int AddObjectIfPossible(int x, int y, OBJECT_NAMES name);

    SDL_Texture* static_saved_drawn_data = SDL_CreateTexture(global_window_data.rdr, NULL, SDL_TEXTUREACCESS_TARGET, tiles_wide * tile_length, tiles_high * tile_length);
    SDL_Texture* texture;
};