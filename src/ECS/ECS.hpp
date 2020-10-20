#pragma once

#include "../sdl.h"

#include "EntityInfo.hpp"
#include "SOA_Entities.hpp"

#include "../Map.hpp"
#include "../Player.hpp"
#include "../Enemies.hpp"

class Map;
class Enemies;

struct ECS {

    void GiveMapPlayerEnemies(Map* _map, Player* _player, Enemies* _enemies);
    int AddEntity(float x, float y, ENTITY_NAME name, ENTITY_TYPE type);

    inline float GetCenterX(int id) { return entities.xs[id] + ENTITY_COLLISION_DATA.xs[entities.names[id]] + ENTITY_COLLISION_DATA.ws[entities.names[id]] / 2; }
    inline float GetCenterY(int id) { return entities.ys[id] + ENTITY_COLLISION_DATA.ys[entities.names[id]] + ENTITY_COLLISION_DATA.hs[entities.names[id]] / 2; }

    void Draw();

    Map* map;
    Player* player;
    Enemies* enemies;

    SOAEntities entities;
    std::vector<int> draw_order_indexes;
};