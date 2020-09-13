#pragma once

#include <vector>
#include <map>

struct SOARects {
    std::vector<int> xs;
    std::vector<int> ys;
    std::vector<int> ws;
    std::vector<int> hs;
};

enum ENTITY_TYPE {
    PLAYER_TYPE,
    MAP_TYPE,
    ENEMY_TYPE
};

enum ENTITY_NAME {
    PLAYER,

    TREE1,
    TREE2,
    LOG,
    STONE,
};

extern const SOARects ENTITY_COLLISION_INFO; // x and y are for offsets
extern const SOARects ENTITY_QUAD_DIMENSIONS;
extern const int MAP_ENTITY_OFFSET;
extern const int NUM_MAP_ENTITY_TYPE;