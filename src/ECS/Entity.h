#pragma once

#include <Engine/Engine.h>

enum ENTITY_TYPE {
    PLAYER_TYPE,
    MAP_TYPE,
    ENEMY_TYPE,
    MINIOBJECT_TYPE
};

struct Entity {

    ENTITY_TYPE type;
    float x;
    float y;
    // This holds collision_box and quad data which is useful for drawing in ECS.
    Asset_Ase** asset = NULL;

    void Draw() {};
};

// A lot entities are going to have similar draw functions,
// so it's worth adding some small inline ones that are easily accessible.
// I'm not making a default draw function because I think that'll make it
// more difficult to see at a glance what entity is using what draw function.

// I was thinking of doing function pointers, but there are many cases such as in
// update where you need higher level data, e.g. all barrel enemies would need
// to access the same variable such as minimum radius to aggravate. And so
// using function pointers for that might make it messy. And doing half function
// pointers half function overrides is even messier.

inline void DrawAnimatedEntity(Entity* e, CurAnimation* anim) {
    RenderCopy(g_window.rdr, (*(e->asset))->texture, & anim->quad, e->x, e->y);
}