#pragma once

#include <vector>
#include <map>
#include <string>

#include <Engine/Engine.h>
#include "ECS/ECS.h"

struct Map;
struct ECS;
struct Player;

struct Barrel {
    float x;
    float y;
    bool aggravated;
    CurAnimation anim;
};

struct Enemies {

    void GivePointers(ECS* _ecs);
    void LoadAssets();
    void DestroyAssets();
    void InitAllEnemies();

    void DrawEnemy(int id);
    void Update();

    void AddBarrel();

    ECS* ecs;

    // Note: Thinking about adding void* to entity in ecs, so that we don't
    // even have to do the lookup. For now not bothering.
    std::map<int, Barrel> barrels;

    Asset_Ase_Animated* barrel_asset = NULL;
};