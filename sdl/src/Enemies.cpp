#include "Enemies.hpp"

void Enemies::CreateTextures() {
    textures[SPIDER] = LoadImage(global_window_data.rdr, "assets/enemies/spider.png");
}

void Enemies::GiveDeltaMap(float* _dt, Map* _map) {
    dt = _dt;
    map = _map;
}

inline void Enemies::AddEnemy(EnemyType type, float x, float y, std::string cur_animation) {
    enemies_data.types.push_back(type);
    enemies_data.xs.push_back(x);
    enemies_data.ys.push_back(y);
    enemies_data.current_animations.push_back(cur_animation);
    enemies_data.animation_timers.push_back(0);
    enemies_data.animation_indexes.push_back(0);
}

void Enemies::CreateEnemies() {
    for (int i = 0; i < 100; i ++) {
        AddEnemy(SPIDER, random(0, map->map_width - 100), random(0, map->map_height - 100), "idle");
    }
}

void Enemies::DrawEnemy(float x, float y, ) {
    EnemyType type = enemies_data.types[i];

    SDL_Rect quad = {frame_index * enemies_animations_data[type].w, enemies_animations_data[type].h * enemies_animations_data[type].offsets[animation_type_index], enemies_animations_data[type].w, enemies_animations_data[type].h};
    SDL_Rect pos =  {enemies_data.xs[i], enemies_data.ys[i], enemies_animations_data[type].w, enemies_animations_data[type].h};

    SDL_RenderCopy(global_window_data.rdr, textures[type], & quad, & pos);
}

void Enemies::Update() {
}