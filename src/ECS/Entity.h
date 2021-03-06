#pragma once

#include <Engine/Engine.h>

enum ENTITY_TYPE {
    PLAYER_TYPE,
    MAP_TYPE,
    ENEMY_TYPE,
    MINIOBJECT_TYPE
};

struct Entity {

    // We aren't actually using the entity types anywhere, but I'd bet that I'll definitely need them for some reason in the future.
    ENTITY_TYPE type;
    float x;
    float y;
    // This holds collision_box and quad data which is useful for drawing in ECS.
    Asset_Ase** asset = NULL;

    virtual void Draw() {};


    // Used by ECS to detect and remove "deleted enemies"
    // We don't actually delete the entity because often times we reuse it differently.
    // E.g. Enemies has a fixed size array of entities. So, instead of deleting one from a flexible array,
    // we can just check in the enemy loop whether it is deleted or not, and ignore it in the array if it's deleted.
    // Then, to add new entities, we can go through the array and fill the deleted entity with the new entity.
    bool deleted = false;
};


// A lot entities are going to have similar draw functions,
// so it's worth adding some small inline ones that are easily accessible.
// I'm not making a default draw function because I think that'll make it
// more difficult to see at a glance what entity is using what draw function.

// I was thinking of doing function pointers, but there are many cases such as in
// enemy update where you need higher level data, e.g. all barrel enemies would need
// to access the same variable such as minimum radius to aggravate, and so
// using function pointers for that might make it messy. And doing half function
// pointers half function overrides is even messier.

inline void DrawAnimatedEntity(Entity* e, CurAnimation* anim) {
    RenderCopy(g_window.rdr, (*(e->asset))->texture, & anim->quad, e->x, e->y);
}