#pragma once

#include "../Globals/Entity.h"

inline bool AABB(float x, float y, float w, float h, float x2, float y2, float w2, float h2) {
    return x + w > x2 && x < x2 + w2 && y + h > y2 && y < y2 + h2;
}

inline bool Entities_AABB(ENTITY_NAME e1, float x1, float y1, ENTITY_NAME e2, float x2, float y2) {
    return AABB(x1 + COLLISION_DATA[e1].x, y1 + COLLISION_DATA[e1].y, COLLISION_DATA[e1].w, COLLISION_DATA[e1].h, x2 + COLLISION_DATA[e2].x, y2 + COLLISION_DATA[e2].y, COLLISION_DATA[e2].w, COLLISION_DATA[e2].h);
}