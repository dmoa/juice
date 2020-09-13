#pragma once

#include "EntityInfo.hpp"
#include "SOAEntities.hpp"

#include "../Map.hpp"
#include "../Player.hpp"
#include "../Enemies.hpp"

class Map;
class Enemies;

struct ECS {

    void GiveMapPlayerEnemies(Map* _map, Player* _player, Enemies* _enemies);
    int AddEntity(float x, float y, ENTITY_NAME name, ENTITY_TYPE type, int id = -1);
    void Sort();
    void Draw();

    Map* map;
    Player* player;
    Enemies* enemies;

    SOAEntities entities;
    std::map<int, int> find_entities;
};