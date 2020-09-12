#pragma once

#include <vector>

#include "ObjectsNames.hpp"
#include "ObjectTypes.hpp"

struct Objects {
    std::vector<float> xs;
    std::vector<float> ys;
    std::vector<OBJECT_NAMES>   names;
    std::vector<OBJECT_TYPES>   types;
    std::vector<int> ids;
};