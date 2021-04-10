#pragma once

#include <algorithm>

#include <Engine/Engine.h>

#include "Entity.h"

struct Map;
struct Player;
struct Enemies;

struct ECS {

    void AddEntity(Entity* e);

    inline float GetCenterX(int id) { return entities[id]->x + (*entities[id]->asset)->frame_width / 2; }
    inline float GetCenterY(int id) { return entities[id]->y + (*entities[id]->asset)->frame_height / 2; }

    void Draw();
    void Update();

    // I know, vectors are bad, please forgive me :|
    std::vector<Entity*> entities;
    std::vector<int> draw_order_indexes; // order they're drawn in.
};