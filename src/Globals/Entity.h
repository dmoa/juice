#pragma once

#include <vector>
#include <string>
#include <unordered_map>

#include <SDL_CP.h>
#include "../ECS/Classification.h"

// for ANIMATION_DATA only.
struct AnimationInfo {
    int num_frames;
    float speed;
    int spreadsheet_index_y; // for calculating correct row for spritesheet
};

struct CurrAnimation {
    ANIMATION_TYPE type;
    float          tick;
    int            frame;
};

extern const SDL_Rect COLLISION_DATA  []; // x and y are for offsets
extern const SDL_Rect QUAD_DIMENSIONS [];
// not const just so we can use []. I know, very lazy.
extern std::unordered_map<ENTITY_NAME, std::unordered_map<ANIMATION_TYPE, AnimationInfo> > ANIMATION_DATA;
extern const int MAP_ENTITY_OFFSET;
extern const int NUM_MAP_ENTITY_TYPE;