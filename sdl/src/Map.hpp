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

struct ObjectQuads {
    std::vector<int> xs;
    std::vector<int> ys;
    std::vector<int> ws;
    std::vector<int> hs;
};

struct Objects {
    std::vector<int> xs;
    std::vector<int> ys;
    std::vector<int> quad_indexes;
};

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

    ObjectQuads object_quads;
    inline void AddQuad(int x, int y, int w, int h) {
        object_quads.xs.push_back(x);
        object_quads.ys.push_back(y);
        object_quads.ws.push_back(w);
        object_quads.hs.push_back(h);
    }

    Objects objects;
    inline void AddObject(int x, int y, int quad_index) {
        objects.xs.push_back(x);
        objects.ys.push_back(y);
        objects.quad_indexes.push_back(quad_index);
    }

    SDL_Rect iter_quad;
    SDL_Rect iter_pos;
    SDL_Texture* texture;
    SDL_Texture* static_saved_drawn_data = SDL_CreateTexture(global_window_data.rdr, NULL, SDL_TEXTUREACCESS_TARGET, tiles_wide * tile_length, tiles_high * tile_length);
};