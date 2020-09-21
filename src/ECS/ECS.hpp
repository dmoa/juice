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
    void Draw();

    Map* map;
    Player* player;
    Enemies* enemies;

    SOAEntities entities;
    std::vector<int> draw_order_indexes;
};