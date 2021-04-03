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
    Asset_Ase** asset;
    void (*Draw)(Entity*);
    void (*Update)(Entity*);
};

struct Animated_Entity : Entity {
    CurAnimation anim;
};

struct Barrel : Animated_Entity {
    bool aggravated;
    float timer;
}

void DrawAnimatedEntity(Entity* e) {
    Animated_Entity* entity = (Animated_Entity*) e;

    RenderCopy(g_window.rdr, (*(entity->asset))->texture, & entity->anim.quad, entity->x, entity->y);
}