#pragma once

#include <algorithm>

#include <Engine/Engine.h>

#include "Entity.h"

struct Map;
struct Player;
struct Enemies;

struct ECS {

    void GivePointers(Map* _map, Player* _player, Enemies* _enemies);

    void AddEntity(Entity* e)

    // @TODO
    // Change so that every entity has a draw and update function pointer, so that we don't need to do massive switch statements.
    // Completely change the structure of enemies and probably player, so that Entity stores a void pointer to data. Casey Muratori style, I think!?

    inline float GetCenterX(int id) { return entities[id].x + (*entities[id].asset)->frame_width / 2; }
    inline float GetCenterY(int id) { return entities[id].y + (*entities[id].asset)->frame_height / 2; }

    void Draw();

    Map* map;
    Player* player;
    Enemies* enemies;

    std::vector<Entity*> entities;
    std::vector<int> draw_order_indexes; // order they're drawn in.
};