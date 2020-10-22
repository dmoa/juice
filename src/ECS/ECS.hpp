#pragma once

#include "../sdl.h"

#include "EntityInfo.hpp"
#include "SOA_Entity.hpp"

#include "../Map.hpp"
#include "../Player.hpp"
#include "../Enemies.hpp"

class Map;
class Enemies;

struct ECS {

    void GiveMapPlayerEnemies(Map* _map, Player* _player, Enemies* _enemies);
    int AddEntity(float x, float y, ENTITY_NAME name, ENTITY_TYPE type);

    inline float GetCenterX(int id) { return entities[id].x + ENTITY_COLLISION_DATA[entities[id].name].x + ENTITY_COLLISION_DATA[entities[id].name].w / 2; }
    inline float GetCenterY(int id) { return entities[id].y + ENTITY_COLLISION_DATA[entities[id].name].y + ENTITY_COLLISION_DATA[entities[id].name].h / 2; }

    void Draw();

    Map* map;
    Player* player;
    Enemies* enemies;

    std::vector<SOA_Entity> entities;
    std::vector<ENTITY_TYPE> entity_types; // not accessed often with entities, so seperate from SOAEntities, #DataOrientatedFTW

    std::vector<int> draw_order_indexes;
};