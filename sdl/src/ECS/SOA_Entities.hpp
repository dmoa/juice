#pragma once

#include <vector>

#include "EntityInfo.hpp"

struct SOAEntities {
    std::vector<ENTITY_NAME>   names;
    std::vector<ENTITY_TYPE>   types;
    std::vector<int> ids;
    std::vector<float> xs;
    std::vector<float> ys;

    // not all entities have animations, if they don't, they'll have index -1.
    std::vector<int> animation_indexes;
    std::vector<std::string> current_animations;
    std::vector<float> timers;
    std::vector<int>   current_frames;
};