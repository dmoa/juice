#pragma once

#include <vector>

#include "EntityInfo.hpp"

struct SOAEntities {
    std::vector<ENTITY_NAME>   names;
    std::vector<ENTITY_TYPE>   types;
    std::vector<float> xs;
    std::vector<float> ys;
};