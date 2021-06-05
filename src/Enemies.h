#pragma once

#include <vector>
#include <map>
#include <string>

#include <Engine/Engine.h>
#include "ECS/ECS.h"
#include "ECS/Max.h"
#include "Player.h"

struct Map;
struct ECS;
struct Player;

struct Barrel : Entity {

    void Draw();

    CurAnimation anim;
    bool aggravated = false;
    float agg_timer = -1;

    // How long before barrel can do damage again.
    float attack_timer = -1;
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

    Barrel barrels [MAX_ENEMIES];

    Asset_Ase_Animated* barrel_asset = NULL;
    int barrel_range = 30;
    int barrel_aggr_time = 4;
    float barrel_attack_interval;
    int barrel_damage = 1;
};