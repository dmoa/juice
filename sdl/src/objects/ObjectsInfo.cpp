#include "ObjectsInfo.hpp"

// x, y, w, h
const SOARects OBJECTS_QUAD_INFO = {
    {0, 16, 32, 32},
    {32, 32, 32, 48},
    {16, 16, 16, 16},
    {32, 32, 16, 16},
};

// y offset
// const std::vector<int> OBJECTS_DRAW_ORDER_OFFSET = {32, 32, };

// x offset from draw position,
// y offset from draw position,
// width of collision box,
// height of collision box.
const SOARects OBJECTS_COLLISION_INFO = {
    {1, 1, 1, 1},
    {1, 1, 2, 2},
    {14, 14, 14},
    {29, 29, 12},
};