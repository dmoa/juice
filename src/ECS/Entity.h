#pragma once

#include "Classification.h"

struct Entity {
    ENTITY_TYPE type;
    float x;
    float y;
    // This holds collision_box and quad data which is useful for drawing in ECS.
    Asset_Ase** asset;
};