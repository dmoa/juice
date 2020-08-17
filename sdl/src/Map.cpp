#include "Map.hpp"

void Map::LoadTexture() {
    texture = IMG_LoadTexture(global_window_data.rdr, "assets/tileset.png");
    if (!texture) SDL_Log("tileset.png not found");
}

void Map::CreateMapTexture() {


    SDL_SetRenderTarget(global_window_data.rdr, saved_drawn_data);

    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 40; j++) {
            iter_pos.x = i * 16 * global_window_data.scale;
            iter_pos.y = j * 16 * global_window_data.scale;
            iter_quad.x = (rand() % 5) * 16;
            SDL_RenderCopy(global_window_data.rdr, texture, & iter_quad, & iter_pos);
        }
    }
    SDL_SetRenderTarget(global_window_data.rdr, NULL);
}

void Map::Draw() {
    SDL_RenderCopy(global_window_data.rdr, saved_drawn_data, NULL, NULL);
}

void Map::DestroyTextures() {
    SDL_DestroyTexture(saved_drawn_data);
    SDL_DestroyTexture(texture);
}