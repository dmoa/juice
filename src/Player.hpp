#pragma once

#include <string>
#include <map>
#define ROOT2 1.41421356237

#include "sdl.h"

#include "utils/LoadImage.hpp"
#include "utils/Controls.hpp"
#include "utils/AABB.hpp"
#include "utils/SOARects.hpp"

#include "GlobalWindowData.hpp"

#include "ECS/ECS.hpp"
#include "ECS/Animation/UpdateAnimation.hpp"

class Map;
class ECS;

struct Player {
    void LoadTexture();
    void DestroyTexture();

    void GiveMapDeltaECS(Map* _map, float* _dt, ECS* _ecs);
    void InitPos();

    void Draw();

    void Update();
    void CollisionUpdate();
    void AnimationUpdate();

    void Attack();

    float x = 10;
    float y = 10;

    const int quad_w = ENTITY_QUAD_DIMENSIONS[PLAYER].w;
    const int quad_h = ENTITY_QUAD_DIMENSIONS[PLAYER].h;

    float GetDrawCenterX() { return x + rendering_quad.w / 2; };
    float GetDrawCenterY() { return y + rendering_quad.h / 2; };

    SDL_Texture* texture;

    float* dt;
    Map* map;
    ECS* ecs;

    // for lookup in ecs,
    // so that we can set the correct pos for the player in ecs,
    // so it can figure out the correct draw order.
    int id;

    float old_x = 50;
    float old_y = 50;
    float current_xv = 0;
    float current_yv = 0;
    int   v = 110;

    bool holding_action_button = false;
    bool is_attacking;
    float cooldown = 0.39;
    float cooldown_tick = cooldown;

    std::vector<SDL_Rect>* map_cb;

    std::string curr_animation = "idle";
    float       animation_tick = 0;
    int         curr_animation_frame = 1;

    SDL_Rect     spritesheet_quad = {0, 0, quad_w, quad_h};
    SDL_Rect     rendering_quad = {-1, -1, quad_w, quad_h};
    SDL_RendererFlip is_flipped = SDL_FLIP_NONE;
};


// @TODO try instead of stopping the player, to make the attack only available when still