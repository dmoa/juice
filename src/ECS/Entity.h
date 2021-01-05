#pragma once

#include "Classification.h"
#include "../Asset/AssetLoader.h"

struct Entity {
    ENTITY_NAME name;
    ENTITY_TYPE type;
    float x;
    float y;

    // This holds collision_box which is useful for draw order in ECS.
    Asset_Ase* asset;
};