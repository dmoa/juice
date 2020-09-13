#include "EntityInfo.hpp"

// x offset from draw position,
// y offset from draw position,
// width of collision box,
// height of collision box.
const SOARects ENTITY_COLLISION_INFO = {
    {8, 5, 1, 1, 1},
    {16, 26, 1, 2, 2},
    {8, 6, 14, 14, 14},
    {2, 5, 29, 12, 12},
};

// @TODO
// replace with SOARects and use the x and y, and for animated stuff just pick the best frame, best case super useful, worst case, not much harm at all.
const SOARects ENTITY_QUAD_DIMENSIONS = {
    {0, 0, 16, 32, 32},
    {0, 32, 32, 32, 48},
    {24, 16, 16, 16, 16},
    {18, 32, 32, 16, 16},
};

// ObjectNames enum has more than just map objects. MAP_ENTITY_OFFSET only needs to store static map objects. Therefore, we need
// an offset for STATIC_QUADS_INFO and ecs->objects to match up.
// TREE1 is the first map object in ObjectNames.
const int MAP_ENTITY_OFFSET = TREE1;
const int NUM_MAP_ENTITY_TYPE = 4;