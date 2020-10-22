#pragma once

#include <vector>
#include <map>
#include <string>

#include "../utils/SOARects.hpp"
#include "../sdl.h"

#include "Data/EntityType.hpp"
#include "Data/EntityName.hpp"

struct Animation {
    const std::string type;
    int num_frames;
    int speed;
};

extern const SDL_Rect ENTITY_COLLISION_DATA  []; // x and y are for offsets
extern const SDL_Rect ENTITY_QUAD_DIMENSIONS [];
extern std::map<ENTITY_NAME, SOAAnimations> ENTITY_ANIMATION_DATA; // not const just so we can use []. I know, very lazy.
extern const int MAP_ENTITY_OFFSET;
extern const int NUM_MAP_ENTITY_TYPE;