#pragma once

#include "../sdl.h"

#include "../Globals/All.h"
#include "SOA_Entity.h"

struct Map;
struct Player;
struct Enemies;

struct ECS {

    void GiveMapPlayerEnemies(Map* _map, Player* _player, Enemies* _enemies);
    int AddEntity(float x, float y, ENTITY_NAME name, ENTITY_TYPE type);

    inline float GetCenterX(int id) { return entities[id].x + COLLISION_DATA[entities[id].name].x + COLLISION_DATA[entities[id].name].w / 2; }
    inline float GetCenterY(int id) { return entities[id].y + COLLISION_DATA[entities[id].name].y + COLLISION_DATA[entities[id].name].h / 2; }

    void Draw();

    Map* map;
    Player* player;
    Enemies* enemies;

    std::vector<SOA_Entity> entities;
    std::vector<ENTITY_TYPE> entity_types; // not accessed often with entities, so seperate from SOAEntities, #DataOrientatedFTW

    std::vector<int> draw_order_indexes;
};