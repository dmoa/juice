#include "Enemies.hpp"

void Enemies::CreateTextures() {
   spider_texture = LoadImage(global_window_data.rdr, "assets/enemies/spider.png");
}

void Enemies::GiveDeltaMapECS(float* _dt, Map* _map, ECS* _ecs) {
    dt = _dt;
    map = _map;
    ecs = _ecs;
}

void Enemies::CreateEnemies() {
    for (int i = 0; i < 100; i ++) {
        int id = ecs->AddEntity(random(50, map->map_width - 100), random(50, map->map_height - 100), SPIDER, ENEMY_TYPE);

        cur_animations.names.push_back("idle");
        cur_animations.cur_frames.push_back(0);
        cur_animations.ticks.push_back(0);
        cur_animations.id_to_index[id] = cur_animations.ticks.size() - 1;
    }
}

void Enemies::DrawEnemy(int id) {

    int i = cur_animations.id_to_index[id];

    SDL_Rect quad;
    SDL_Rect pos;

    UpdateAnimationQuad(cur_animations.names[i], cur_animations.cur_frames[i], SPIDER, & quad.x, & quad.y);
    quad.w = pos.w = ENTITY_QUAD_DIMENSIONS.ws[ecs->entities.names[id]];
    quad.h = pos.h = ENTITY_QUAD_DIMENSIONS.hs[ecs->entities.names[id]];
    pos.x = ecs->entities.xs[id];
    pos.y = ecs->entities.ys[id];

    SDL_RenderCopy(global_window_data.rdr, spider_texture, & quad, & pos);
}

void Enemies::Update() {
    // info.first  -> entity id
    // info.second -> index for all cur_animations

    for (auto & info : cur_animations.id_to_index) {
        int j = info.second;

        AnimationTick(dt, & cur_animations.names[j], & cur_animations.ticks[j], & cur_animations.cur_frames[j], ecs->entities.names[info.first]);
    }
}