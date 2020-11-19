#include "MiniObjects.h"

void MiniObjects::GiveDTECS(float* _dt, ECS* _ecs) {
    dt = _dt;
    ecs = _ecs;
}

void MiniObjects::Draw(int id) {
    SDL_Rect quad;
    SDL_Rect pos;

    UpdateAnimationQuad(ecs->entities[id].name, & objects[id].cur_anim, & quad);
    pos = {ecs->entities[id].x, ecs->entities[id].y, quad.w, quad.h};

    SDL_RenderCopyEx(global_window_data.rdr, cobweb_texture, & quad, & pos, NULL, NULL, objects[id].is_right ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
}

void MiniObjects::Update() {
    // it.first  -> entity id
    // it.second -> object struct with additional components

    for (auto & it: objects) {

    }
}

int MiniObjects::GenerateCobweb(float x, float y) {
    int id = ecs->AddEntity(x, y, COBWEB, MINIOBJECT_TYPE);

    objects[id] = {-15, true, {ANIM_NONE}};

    return id;
}