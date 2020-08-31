#pragma once

#include <string>
#include <map>
#define ROOT2 1.41421356237;

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "GlobalWindowData.hpp"
#include "utils/LoadImage.hpp"
#include "utils/Controls.hpp"
#include "AABB.hpp"
#include "CollisionBoxes.hpp"
#include "ExtraCollisionInfo.hpp"
#include "CurrentAnimationData.hpp"
#include "AnimationsData.hpp"

class Map;

class Player {
public:
    void LoadTexture();
    void GiveMapDelta(Map* _map, float* _dt);
    void Draw();
    void Update();
    void CollisionUpdate();
    void AnimationUpdate();
    void SetAnimationIfShould(std::string name);
    void DestroyTexture();

    float GetCenterX() { return x + rendering_quad.w / 2; };
    float GetCenterY() { return y + rendering_quad.h / 2; };
    float GetBottomCollisionY() { return y + rendering_quad.h + extra_collision_info.h; };

private:
    float* dt;
    Map* map;

    float x = 720.f;
    float y = 50;
    float old_x = 50;
    float old_y = 50;
    float current_xv = 0;
    float current_yv = 0;
    int   v = 110;

    CollisionBoxes* map_cb;
    ExtraCollisionInfo extra_collision_info = {8, 16, 8, 2};


    AnimationsData animations_data = {
        16, 16,
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