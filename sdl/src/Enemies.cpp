#include "Enemies.hpp"

void Enemies::CreateTextures() {
    textures[SPIDER] = LoadImage(global_window_data.rdr, "assets/enemies/spider.png");
}

void Enemies::GiveDelta(float* _dt) {
    dt = _dt;
}

void Enemies::Draw() {
    for (unsigned int i = 0; i < enemies_data.xs.size(); i ++) {
        EnemyType type = enemies_data.enemy_types[i];
        int animation_i = 0;
        SDL_Rect quad = {0, 0, enemies_animations_data[type].w, enemies_animations_data[type].h};
        SDL_Rect pos =  {enemies_data.xs[i],enemies_data.ys[i], enemies_animations_data[type].w, enemies_animations_data[type].h};
        SDL_RenderCopy(global_window_data.rdr, textures[type], & quad, & pos);
    }
}

void Enemies::Update() {

}