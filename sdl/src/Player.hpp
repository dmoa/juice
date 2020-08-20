#pragma once

#include <string>
#include <map>
#define ROOT2 1.41421356237;

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "GlobalWindowData.hpp"
#include "AABB.hpp"
#include "CollisionBoxes.hpp"
#include "CurrentAnimationData.hpp"
#include "AnimationsData.hpp"

#include "Map.hpp"

// This is used when the quad dimensions of the spritesheet are not the same as collision boxes we want,
// e.g. big quad of a player, but we only want the feet to be the collision box.
struct ExtraCollisionInfo {
    int offset_x;
    int offset_y;
    int w;
    int h;
};

class Player {
public:
    void LoadTexture();
    void GiveDT(float* _dt) { dt = _dt; }
    void GiveMap(Map* _map) {
        map = _map;
        map_cb = map->GetCollisionBoxes();
    };
    void Draw();
    void Update();
    void CollisionUpdate();
    void AnimationUpdate();
    void SetAnimationIfShould(std::string name);
    void DestroyTexture();

    float GetX() { return x; }
    float GetY() { return y; }
private:
    float* dt;
    Map* map;

    float x = 50;
    float old_x = 50;
    float y = 50;
    float old_y = 50;
    float current_xv = 0;
    float current_yv = 0;
    int   v = 80;

    CollisionBoxes* map_cb;
    ExtraCollisionInfo extra_collision_info = {8, 16, 8, 2};


    AnimationsData animations_data = {
        {{"idle",0}, {"running",1}},
        { 4,      6       },
        { 0.3,    0.1     },
        { 0,      4       }
    };

    CurrentAnimationData current_animation = {"idle", 0, 0, 0, animations_data.num_frames[0], animations_data.speeds[0]};

    SDL_Rect     current_spritesheet_quad = {0, 0, 24, 18};
    SDL_Rect     rendering_quad = {x, y, 24, 18};
    SDL_Texture* texture;
    SDL_RendererFlip is_flipped = SDL_FLIP_NONE;
};