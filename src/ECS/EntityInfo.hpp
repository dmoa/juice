#pragma once

#include <vector>
#include <string>
#include <unordered_map>

#include "../utils/SOARects.hpp"
#include "../sdl.h"

#include "Data/EntityType.hpp"
#include "Data/EntityName.hpp"

enum ANIMATION_TYPE {
    IDLE,
    RUN,
    ATTACK
};

// for ANIMATION_DATA only.
struct AnimationInfo {
    int num_frames;
    float speed;
    int spreadsheet_index_y; // for calculating correct row for spritesheet
};

struct CurrAnimation {
    float          tick;
    int            frame;
};

extern const SDL_Rect ENTITY_COLLISION_DATA  []; // x and y are for offsets
extern const SDL_Rect ENTITY_QUAD_DIMENSIONS [];
// not const just so we can use []. I know, very lazy.
// @TODO ADD CONST
extern std::unordered_map<ENTITY_NAME, std::unordered_map<ANIMATION_TYPE, AnimationInfo> > ANIMATION_DATA;
extern const int MAP_ENTITY_OFFSET;
extern const int NUM_MAP_ENTITY_TYPE;