#include "Map.hpp"

void Map::LoadTexture() {
    texture = IMG_LoadTexture(global_window_data.rdr, "assets/tileset.png");
    if (!texture) SDL_Log("tileset.png not found");
}

void Map::CreateMapTexture() {
    SDL_SetRenderTarget(global_window_data.rdr, saved_drawn_data);
    SDL_RenderSetScale(global_window_data.rdr, 1, 1);

    SDL_Rect iter_quad = {0, 0, 16, 16};
    SDL_Rect iter_pos  = {0, 0, 16, 16};

    for (int i = 1; i < tiles_wide - 1; i++) {
        for (int j = 1; j < tiles_high - 1; j++) {
            iter_pos.x = i * 16;
            iter_pos.y = j * 16;
            iter_quad.x = (rand() % 5) * 16;
            SDL_RenderCopy(global_window_data.rdr, texture, & iter_quad, & iter_pos);
        }
    }

    iter_quad.y = 16; // switching to row of water quads

    iter_quad.x = 48;

    iter_pos.x = iter_pos.y = 0;
    SDL_RenderCopy(global_window_data.rdr, texture, & iter_quad, & iter_pos);
    iter_pos.x = (tiles_wide - 1) * 16;
    SDL_RenderCopy(global_window_data.rdr, texture, & iter_quad, & iter_pos);
    iter_pos.x = iter_pos.y = 0, (tiles_high - 1) * 16;
    SDL_RenderCopy(global_window_data.rdr, texture, & iter_quad, & iter_pos);
    iter_pos.x = (tiles_wide - 1) * 16;
    SDL_RenderCopy(global_window_data.rdr, texture, & iter_quad, & iter_pos);

    iter_quad.x = 80;
    for (int i = 1; i < tiles_wide - 1; i++) {
        iter_pos.x = i * 16;
        SDL_RenderCopy(global_window_data.rdr, texture, & iter_quad, & iter_pos);
    }

    iter_quad.x = 32;
    iter_pos.x = 0;
    for (int i = 1; i < tiles_high - 1; i++) {
        iter_pos.y = i * 16;
        SDL_RenderCopyEx(global_window_data.rdr, texture, & iter_quad, & iter_pos, NULL, NULL, SDL_FLIP_HORIZONTAL);
    }


    SDL_SetRenderTarget(global_window_data.rdr, NULL);
    SDL_RenderSetScale(global_window_data.rdr, global_window_data.scale, global_window_data.scale);
}

void Map::Draw() {
    map_rendering_quad = {0, 0, global_window_data.w / global_window_data.scale + 20, global_window_data.h / global_window_data.scale + 20};
    SDL_RenderCopy(global_window_data.rdr, saved_drawn_data, & map_rendering_quad, NULL);
}

void Map::DestroyTextures() {
    SDL_DestroyTexture(saved_drawn_data);
    SDL_DestroyTexture(texture);
}