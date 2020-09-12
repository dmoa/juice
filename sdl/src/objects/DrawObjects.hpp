#pragma once

#include "ObjectsNames.hpp"
#include "ObjectTypes.hpp"

#include "../Map.hpp"
#include "../Player.hpp"
#include "../Enemies.hpp"

class Map;
class DrawObjects;

struct DrawObjects {

    void GiveMapPlayerEnemies(Map* _map, Player* _player, Enemies* _enemies);
    int AddObject(float x, float y, OBJECT_NAMES name, OBJECT_TYPES type, int id = -1);
    void Sort();
    void Draw();

    Map* map;
    Player* player;
    Enemies* enemies;

    Objects objects;
    std::map<int, int> find_objects;
};