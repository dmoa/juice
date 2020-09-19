#pragma once

#include <string>
#include <map>
#define ROOT2 1.41421356237;

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "utils/LoadImage.hpp"
#include "utils/Controls.hpp"
#include "utils/AABB.hpp"
#include "utils/SOARects.hpp"

#include "GlobalWindowData.hpp"

#include "ECS/ECS.hpp"
#include "ECS/Animation/UpdateAnimation.hpp"

class Map;
class ECS;

class Player {
public:
    void LoadTexture();
    void GiveMapDeltaECS(Map* _map, float* _dt, ECS* _ecs);
    void InitPos();
    void Draw();
    void Update();
    void CollisionUpdate();
    void AnimationUpdate();
    void SetAnimationIfShould(std::string name);
    void DestroyTexture();


    float x = 30;
    float y = 50;

    const int quad_w = ENTITY_QUAD_DIMENSIONS.ws[PLAYER];
    const int quad_h = ENTITY_QUAD_DIMENSIONS.hs[PLAYER];

    float GetCenterX() { return x + rendering_quad.w / 2; };
    float GetCenterY() { return y + rendering_quad.h / 2; };

    SDL_Texture* texture;
private:
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

    SOARects* map_cb;

    std::string curr_animation = "idle";
    float       animation_tick = 0;
    int         curr_animation_frame = 1;

    SDL_Rect     spritesheet_quad = {0, 0, quad_w, quad_h};
    SDL_Rect     rendering_quad = {-1, -1, quad_w, quad_h};
    SDL_RendererFlip is_flipped = SDL_FLIP_NONE;
};