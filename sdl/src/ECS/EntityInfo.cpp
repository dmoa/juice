#include "EntityInfo.hpp"

// x offset from draw position,
// y offset from draw position,
// width of collision box,
// height of collision box.
const SOARects ENTITY_COLLISION_INFO = {
    {8, 5, 1, 1, 1, 9},
    {16, 26, 1, 2, 2, 24},
    {8, 6, 14, 14, 14, 14},
    {2, 5, 29, 12, 12, 9},
};

const SOARects ENTITY_QUAD_DIMENSIONS = {
    {0, 0, 16, 32, 32, 0},
    {0, 32, 32, 32, 48, 0},
    {24, 16, 16, 16, 16, 32},
    {18, 32, 32, 16, 16, 32},
};

// We use these to generate the correct enums when
// generating map objects in map.cpp.
const int MAP_ENTITY_OFFSET = TREE1;
const int NUM_MAP_ENTITY_TYPE = 4;