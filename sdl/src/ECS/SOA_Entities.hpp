#pragma once

#include <vector>

#include "EntityInfo.hpp"

struct SOAEntities {
    std::vector<ENTITY_NAME>   names;
    std::vector<ENTITY_TYPE>   types;
    std::vector<int> ids;
    std::vector<float> xs;
    std::vector<float> ys;
    std::vector<int> animation_data_index;
};