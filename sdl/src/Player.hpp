#pragma once

#include <string>
#include <map>
#define ROOT2 1.41421356237;

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "utils/LoadImage.hpp"
#include "utils/Controls.hpp"
#include "utils/AABB.hpp"
#include "utils/CollisionBoxes.hpp"
#include "utils/ExtraCollisionInfo.hpp"
#include "utils/CurrentAnimationData.hpp"
#include "utils/AnimationsData.hpp"

#include "GlobalWindowData.hpp"

#include "objects/ObjectsNames.hpp"
#include "objects/ObjectsInfo.hpp"
#include "objects/DrawObjects.hpp"

class Map;
class DrawObjects;

class Player {
public:
    void LoadTexture();
    void GiveMapDeltaDrawObjects(Map* _map, float* _dt, DrawObjects* _draw_objects);
    void InitPos();
    void Draw();
    void Update();
    void CollisionUpdate();
    void AnimationUpdate();
    void SetAnimationIfShould(std::string name);
    void DestroyTexture();

    float GetCenterX() { return x + rendering_quad.w / 2; };
    float GetCenterY() { return y + rendering_quad.h / 2; };
    float GetBottomCollisionY() { return y + rendering_quad.h + collision_info.h; };

    ExtraCollisionInfo collision_info = {8, 16, 8, 2};
    float x = 30;
    float y = 50;

    const int quad_w = OBJECTS_QUAD_DIMENSIONS.ws[PLAYER];
    const int quad_h = OBJECTS_QUAD_DIMENSIONS.hs[PLAYER];

    SDL_Texture* texture;
private:
    float* dt;
    Map* map;
    DrawObjects* draw_objects;

    // for lookup in draw_objects,
    // so that we can set the correct pos for the player in draw_objects,
    // so it can figure out the correct draw order.
    int id;

    float old_x = 50;
    float old_y = 50;
    float current_xv = 0;
    float current_yv = 0;
    int   v = 110;

    CollisionBoxes* map_cb;


    AnimationsData animations_data = {
        16, 16,
        {{"idle",0}, {"running",1}},
        { 4,      6       },
        { 0.3,    0.1     },
        { 0,      4       }
    };

    CurrentAnimationData current_animation = {"idle", 0, 0, 0, animations_data.num_frames[0], animations_data.speeds[0]};

    SDL_Rect     current_spritesheet_quad = {0, 0, quad_w, quad_h};
    SDL_Rect     rendering_quad = {x, y, quad_w, quad_h};
    SDL_RendererFlip is_flipped = SDL_FLIP_NONE;
};