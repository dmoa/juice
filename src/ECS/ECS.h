#pragma once

#include <algorithm>

#include <Engine/Engine.h>

#include "Entity.h"
#include "Max.h"

struct Map;
struct Player;
struct Enemies;

struct ECS {

    void Init();

    void AddEntity(Entity* e);

    void Draw();
    void Update();

    int old_num_entities = 0;
    int num_active_entities = 0;
    Entity* entities [MAX_ENTITIES];
};