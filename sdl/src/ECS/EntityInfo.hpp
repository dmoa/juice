#pragma once

#include <vector>
#include <map>
#include <string>

#include "Data/EntityType.hpp"
#include "Data/EntityName.hpp"

struct SOARects {
    std::vector<int> xs;
    std::vector<int> ys;
    std::vector<int> ws;
    std::vector<int> hs;
};

struct SOAAnimations {
    int w;
    int h;
    std::map<std::string, int> animation_types;
    std::vector<int> num_frames;
    std::vector<float> speeds;
    std::vector<int> offsets;
};

extern const SOARects ENTITY_COLLISION_DATA; // x and y are for offsets
extern const SOARects ENTITY_QUAD_DIMENSIONS;
extern const std::map<ENTITY_TYPE, SOAAnimations> ENTITY_ANIMATION_DATA;
extern const int MAP_ENTITY_OFFSET;
extern const int NUM_MAP_ENTITY_TYPE;