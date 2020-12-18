#pragma once

#include <vector>
#include <map>
#include <string>

#include <SDL_CP.h>

#include "utils/extramath.h"
#include "Asset/AssetLoader.h"
#include "Globals/All.h"

struct Map;
struct ECS;
struct Player;

struct Enemy {
    int hp;
    bool is_right;
    CurrAnimation cur_anim;
};

struct Enemies {
    void CreateTextures();
    void GiveDeltaMapECSPlayer(float* _dt, Map* _map, ECS* _ecs, Player* _player);
    void CreateEnemies();
    void DrawEnemy(int id);
    void Update();
    void UpdateEnemyAnimation(int id, Enemy* j);
    void UpdateEnemyMovement(int id, Enemy* j);

    float*  dt;
    Map*    map;
    ECS*    ecs;
    Player* player;

    const int activation_distance   = 50;
    const int deactivation_distance = 80;
    const int attack_distance       = 25;

    // Components on top of ECS for enemy only

    std::map<int, Enemy>  enemies;

    SDL_Texture* spider_texture;
};