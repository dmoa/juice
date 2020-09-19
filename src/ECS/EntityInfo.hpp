#pragma once

#include <vector>
#include <map>
#include <string>

#include "../utils/SOARects.hpp"

#include "Data/EntityType.hpp"
#include "Data/EntityName.hpp"

struct SOAAnimations {
    std::map<std::string, int> animation_types;
    std::vector<int> num_frames;
    std::vector<float> speeds;
};

extern const SOARects ENTITY_COLLISION_DATA; // x and y are for offsets
extern const SOARects ENTITY_QUAD_DIMENSIONS;
extern std::map<ENTITY_NAME, SOAAnimations> ENTITY_ANIMATION_DATA; // not const just so we can use []. I know, very lazy.
extern const int MAP_ENTITY_OFFSET;
extern const int NUM_MAP_ENTITY_TYPE;