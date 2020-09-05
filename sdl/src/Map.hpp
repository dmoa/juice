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
#include "objects/Objects.hpp"
#include "objects/ObjectsNames.hpp"
#include "objects/ObjectsInfo.hpp"

class Player;

class Map {
public:
    void LoadTexture();
    void ReloadTilesetTexture();
    void GivePlayerDelta(Player* _player, float* _dt);
    void CreateMapTexture();
    void CreateCollisionBoxes();
    CollisionBoxes* GetCollisionBoxes() { return & collision_boxes; }
    int GetMapWidth () { return tiles_wide * tile_length; };
    int GetMapHeight() { return tiles_high * tile_length; };
    void DrawBase();
    inline void DrawObject(float x, float y, OBJECT_NAMES name) {
        int i = name - FIRST_MAP_OBJECT_OFFSET;
        SDL_Rect quad = {QUADS_INFO.xs[i], QUADS_INFO.ys[i], QUADS_INFO.ws[i], QUADS_INFO.hs[i]};
        SDL_Rect pos = {x, y, QUADS_INFO.ws[i], QUADS_INFO.hs[i]};
        SDL_RenderCopy(global_window_data.rdr, texture, & quad, & pos);
    }

    void Update();
    void DestroyTextures();

    const int tile_length = 16;
    const int tiles_wide  = 48;
    const int tiles_high  = 48;
    const int map_width   = tile_length * tiles_wide;
    const int map_height  = tile_length * tiles_high;

    const SOARects QUADS_INFO = {
        {0, 16, 32, 32},
        {32, 32, 32, 48},
        {16, 16, 16, 16},
        {32, 32, 16, 16},
    };

    Objects objects;
private:
    float* dt;
    Player* player;

    const int opacity_distance = 50; // minimum distance from player before objects become transparent

    CollisionBoxes collision_boxes;

    // ObjectQuadsInfo object_quads_info;
    // inline void AddQuad(int x, int y, int w, int h, int offset_y) {
    //     object_quads_info.xs.push_back(x);
    //     object_quads_info.ys.push_back(y);
    //     object_quads_info.ws.push_back(w);
    //     object_quads_info.hs.push_back(h);
    //     object_quads_info.draw_order_offset_y.push_back(offset_y);
    // }

        // x, y, w, h


    inline void AddObjectIfPossible(int x, int y, OBJECT_NAMES name);
    inline void AddObject(int x, int y, OBJECT_NAMES name);

    SDL_Rect iter_quad;
    SDL_Rect iter_pos;
    SDL_Texture* static_saved_drawn_data = SDL_CreateTexture(global_window_data.rdr, NULL, SDL_TEXTUREACCESS_TARGET, tiles_wide * tile_length, tiles_high * tile_length);
    SDL_Texture* texture;
};