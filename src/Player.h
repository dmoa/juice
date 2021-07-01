#pragma once

#include <string>
#include <map>

#include <Engine/Engine.h>
#include "ECS/Entity.h"
#include "Crosshair.h"

struct Map;
struct Enemies;
struct ECS;

#define PLAYER_NUM_WEAPONS 1

struct Weapon {
    Asset_Ase* asset;
    SDL_Rect drect;
    v2 pivot;

    float angle; // current angle
    float attack_tick = -1; // time left in the attack

    float attack_length = 0.2;
    float attack_break = 0; // min time in between swings

    int swing_angle = 360; // angle rotated through entire attack

    // Weapon sometimes flipped in attack scenarios.
    SDL_RendererFlip is_flipped = SDL_FLIP_NONE;
};

struct Player : Entity {
    void LoadAsset();
    void DestroyAsset();

    void PassPointers(Map* _map, Enemies* _enemies, ECS* _ecs, Crosshair* _crosshair);
    void InitPos();

    void Draw();
    void DrawCharacter();
    void DrawWeapon();

    void Update();
    void UpdateMovement();
    void UpdateCollision();
    void UpdateAnimation();
    void UpdateWeapon();

    void Attack();
    // We need this because in order to have proper collision detection with enemies,
    // the crosshair has to be updated with the updates player info,
    // so we cannot do enemy collision detection until after the crosshair has been updated.
    void FinishUpdate();

    inline float GetDrawCenterX() { return x + (*asset)->damage_box->x + (*asset)->damage_box->w / 2; };
    inline float GetDrawCenterY() { return y + (*asset)->damage_box->y + (*asset)->damage_box->h / 2; };

    Map* map;
    Enemies* enemies;
    ECS* ecs;
    Crosshair* crosshair;

    // for lookup in ecs,
    // so that we can set the correct pos for the player in ecs,
    // so it can figure out the correct draw order.
    int id;

    float old_x = x;
    float old_y = y;
    float current_xv = 0;
    float current_yv = 0;
    int   v = 110;

    int max_health = 200;
    int current_health = 100;

    bool holding_action_button = false;
    bool is_attacking = false;

    std::vector<SDL_Rect>* map_cb;

    // Using a cheat, because player is an edge case that happens
    // to manage its own asset, i.e. there are not multiple copies
    // of player, so, it can store the pointer to the asset directly.
    Asset_Ase_Animated* _asset = NULL;

    CurAnimation cur_anim;

    SDL_Rect rendering_quad;
    SDL_RendererFlip is_flipped = SDL_FLIP_NONE;

    Weapon weapon;
};