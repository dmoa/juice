#include "ObjectsInfo.hpp"

// y offset
// const std::vector<int> OBJECTS_DRAW_ORDER_OFFSET = {32, 32, };

// x offset from draw position,
// y offset from draw position,
// width of collision box,
// height of collision box.
const SOARects OBJECTS_COLLISION_INFO = {
    {8, 5, 1, 1, 1},
    {16, 26, 1, 2, 2},
    {8, 6, 14, 14, 14},
    {2, 5, 29, 12, 12},
};

const Dimensions OBJECTS_QUAD_DIMENSIONS = {
    {24, 16, 16, 16, 16},
    {18, 32, 32, 16, 16},
};

// ObjectNames enum has more than just map objects. MAP_TYPE_OFFSET only needs to store static map objects. Therefore, we need
// an offset for STATIC_QUADS_INFO and draw_objects->objects to match up.
// TREE1 is the first map object in ObjectNames.
const int MAP_TYPE_OFFSET = TREE1;
const int NUM_MAP_OBJECT_TYPES = 4;