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

struct Enemies {

    void GivePointers(ECS* _ecs, Player* _player);
    void LoadAssets();
    void DestroyAssets();
    void InitAllEnemies();

    void DrawBarrel(Entity* entity);
    void Update();

    void AddBarrel();

    ECS* ecs;
    Player* player;

    // Note: Thinking about adding void* to entity in ecs, so that we don't
    // even have to do the lookup. For now not bothering.
    std::map<int, Barrel> barrels;

    Asset_Ase_Animated* barrel_asset = NULL;
    int barrel_range = 30;
    int barrel_aggr_time = 4;
};