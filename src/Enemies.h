#pragma once

#include <vector>
#include <map>
#include <string>

#include <Engine/Engine.h>
#include "ECS/ECS.h"
#include "Player.h"

struct Map;
struct ECS;
struct Player;

#define NUM_ENEMIES 30

struct Barrel : Entity {

    void Draw();

    CurAnimation anim;
    bool aggravated;
    float timer;
};

struct Enemies {

    void GivePointers(ECS* _ecs, Player* _player);
    void LoadAssets();
    void DestroyAssets();
    void InitAllEnemies();

    void DrawBarrel(Entity* entity);
    void Update();

    ECS* ecs;
    Player* player;

    Barrel barrels [NUM_ENEMIES];

    Asset_Ase_Animated* barrel_asset = NULL;
    int barrel_range = 30;
    int barrel_aggr_time = 4;
};