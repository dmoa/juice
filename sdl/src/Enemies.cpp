#include "Enemies.hpp"

void Enemies::CreateTextures() {
    textures[SPIDER] = LoadImage(global_window_data.rdr, "assets/enemies/spider.png");
}

void Enemies::GiveDelta(float* _dt) {
    dt = _dt;
}

void Enemies::Draw() {
    for (unsigned int i = 0; i < enemies_data.xs.size(); i ++) {
        EnemyType type = enemies_data.types[i];
        int animation_i = enemies_data.animation_indexes[i];

        SDL_Rect quad = {animation_i * enemies_animations_data[type].w, animation_i * enemies_animations_data[type].offsets[i], enemies_animations_data[type].w, enemies_animations_data[type].h};
        SDL_Rect pos =  {enemies_data.xs[i],enemies_data.ys[i], enemies_animations_data[type].w, enemies_animations_data[type].h};

        SDL_RenderCopy(global_window_data.rdr, textures[type], & quad, & pos);
    }
}

void Enemies::Update() {
    for (unsigned int i = 0; i < enemies_data.xs.size(); i ++) {

        enemies_data.animation_timers[i] -= *dt;
        if (enemies_data.animation_timers[i] < 0) {

            EnemyType type = enemies_data.types[i];

            enemies_data.animation_indexes[i] += 1;
            enemies_data.animation_indexes[i] %= enemies_animations_data[type].num_frames[enemies_animations_data[type].names[enemies_data.current_animations[i]]]; // shit code ngl

            enemies_data.animation_timers[i] = enemies_animations_data[type].speeds[enemies_animations_data[type].names[enemies_data.current_animations[i]]];
        }
    }
}