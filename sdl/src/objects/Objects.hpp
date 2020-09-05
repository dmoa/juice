#pragma once

#include <vector>

#include "ObjectsNames.hpp"

struct Objects {
    std::vector<float> xs;
    std::vector<float> ys;
    std::vector<OBJECT_NAMES>   names;
    std::vector<int> ids;
};