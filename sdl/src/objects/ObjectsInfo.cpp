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