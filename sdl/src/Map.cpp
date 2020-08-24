#include "Map.hpp"
#include "Player.hpp"

void Map::LoadTexture() {
    texture = IMG_LoadTexture(global_window_data.rdr, "assets/tileset.png");
    if (!texture) SDL_Log("tileset.png not found");
}

void Map::ReloadTilesetTexture() {
    SDL_DestroyTexture(texture);
    LoadTexture();
}

void Map::CreateMapTexture() {
    SDL_SetRenderTarget(global_window_data.rdr, static_saved_drawn_data);

    iter_quad = {0, 0, tile_length, tile_length};
    iter_pos  = {0, 0, tile_length, tile_length};

    // GRASS TILES

    for (int i = 1; i < tiles_wide - 1; i++) {
        for (int j = 1; j < tiles_high - 1; j++) {
            iter_pos.x = i * tile_length;
            iter_pos.y = j * tile_length;
            iter_quad.x = (rand() % 5) * tile_length;
            SDL_RenderCopy(global_window_data.rdr, texture, & iter_quad, & iter_pos);
        }
    }

    // EDGE WATER TILES

    iter_quad.y = 16; // switching to row of water quads
    iter_quad.x = 48;

    iter_pos.x = iter_pos.y = 0;
    SDL_RenderCopy(global_window_data.rdr, texture, & iter_quad, & iter_pos);
    iter_pos.x = (tiles_wide - 1) * tile_length;
    SDL_RenderCopy(global_window_data.rdr, texture, & iter_quad, & iter_pos);
    iter_pos.x = 0;
    iter_pos.y = (tiles_high - 1) * tile_length;
    SDL_RenderCopy(global_window_data.rdr, texture, & iter_quad, & iter_pos);
    iter_pos.x = (tiles_wide - 1) * tile_length;
    SDL_RenderCopy(global_window_data.rdr, texture, & iter_quad, & iter_pos);

    iter_pos.y = 0;
    iter_quad.x = 80;
    for (int i = 1; i < tiles_wide - 1; i++) {
        iter_pos.x = i * tile_length;
        SDL_RenderCopy(global_window_data.rdr, texture, & iter_quad, & iter_pos);
    }

    iter_quad.x = 32;
    iter_pos.x = 0;
    for (int i = 1; i < tiles_high - 1; i++) {
        iter_pos.y = i * tile_length;
        SDL_RenderCopyEx(global_window_data.rdr, texture, & iter_quad, & iter_pos, NULL, NULL, SDL_FLIP_HORIZONTAL);
    }

    iter_pos.x = (tiles_wide - 1) * tile_length;
    for (int i = 1; i < tiles_high - 1; i++) {
        iter_pos.y = i * tile_length;
        SDL_RenderCopy(global_window_data.rdr, texture, & iter_quad, & iter_pos);
    }

    iter_quad.x = 80;
    iter_pos.y = (tiles_high - 1) * tile_length;
    for (int i = 1; i < tiles_wide - 1; i++) {
        iter_pos.x = i * tile_length;
        SDL_RenderCopyEx(global_window_data.rdr, texture, & iter_quad, & iter_pos, NULL, NULL, SDL_FLIP_VERTICAL);
    }


    // CREATING QUADS FOR NON-GROUND TILES / OBJECTS

    AddQuad(0, tile_length * 2, tile_length, tile_length * 2, 32);
    AddQuad(tile_length, tile_length * 2, tile_length, tile_length * 2, 32);
    AddQuad(tile_length * 2, tile_length * 2, tile_length, tile_length, 15);
    AddQuad(tile_length * 2, tile_length * 3, tile_length, tile_length, 15);


    // TREES, LOGS AND STONES

    int x;
    int y;
    for (int i = 0; i < 500; i++) {
        x = random(tile_length, GetMapWidth() - tile_length * 2);
        y = random(tile_length, GetMapHeight() - tile_length * 3);
        AddObject(x, y, rand() % 4);
    }

    SDL_SetRenderTarget(global_window_data.rdr, NULL);
}

void Map::CreateCollisionBoxes() {

    // EDGE WATER TILES

    collision_boxes.xs.push_back(0);
    collision_boxes.ys.push_back(0);
    collision_boxes.ws.push_back(tile_length);
    collision_boxes.hs.push_back((tiles_high - 1) * tile_length);

    collision_boxes.xs.push_back(tile_length);
    collision_boxes.ys.push_back(0);
    collision_boxes.ws.push_back((tiles_wide - 1) * tile_length);
    collision_boxes.hs.push_back(tile_length);

    collision_boxes.xs.push_back((tiles_wide - 1) * tile_length);
    collision_boxes.ys.push_back(tile_length);
    collision_boxes.ws.push_back(tile_length);
    collision_boxes.hs.push_back((tiles_high - 1) * tile_length);

    collision_boxes.xs.push_back(0);
    collision_boxes.ys.push_back((tiles_high - 1) * tile_length);
    collision_boxes.ws.push_back((tiles_wide - 1) * tile_length);
    collision_boxes.hs.push_back(tile_length);
}

void Map::DrawFirst() {
    SDL_RenderCopy(global_window_data.rdr, static_saved_drawn_data, NULL, NULL);

    for (unsigned int i = 0; i < objects.xs.size(); i++) {
        if (! objects.draw_after_player[i]) {
            iter_quad = {object_quads_info.xs[objects.quad_indexes[i]], object_quads_info.ys[objects.quad_indexes[i]], object_quads_info.ws[objects.quad_indexes[i]], object_quads_info.hs[objects.quad_indexes[i]]};
            iter_pos  = {objects.xs[i], objects.ys[i], object_quads_info.ws[objects.quad_indexes[i]], object_quads_info.hs[objects.quad_indexes[i]]};
            SDL_SetTextureAlphaMod(texture, (int) objects.opacities[i]);
            SDL_RenderCopy(global_window_data.rdr, texture, & iter_quad, & iter_pos);
        }
    }
}

void Map::DrawSecond() {
    for (unsigned int i = 0; i < objects.xs.size(); i++) {
        if (objects.draw_after_player[i]) {
            iter_quad = {object_quads_info.xs[objects.quad_indexes[i]], object_quads_info.ys[objects.quad_indexes[i]], object_quads_info.ws[objects.quad_indexes[i]], object_quads_info.hs[objects.quad_indexes[i]]};
            iter_pos  = {objects.xs[i], objects.ys[i], object_quads_info.ws[objects.quad_indexes[i]], object_quads_info.hs[objects.quad_indexes[i]]};
            SDL_SetTextureAlphaMod(texture, (int) objects.opacities[i]);
            SDL_RenderCopy(global_window_data.rdr, texture, & iter_quad, & iter_pos);
        }
    }
}

void Map::Update() {
    for (unsigned int i = 0; i < objects.xs.size(); i++) {
        if (pyth(objects.xs[i] + object_quads_info.ws[objects.quad_indexes[i]] / 2, objects.ys[i] + object_quads_info.hs[objects.quad_indexes[i]] / 2, player->GetCenterX(), player->GetCenterY()) < opacity_distance) {
            objects.opacities[i] = max(objects.opacities[i] - (*dt) * 500, 130.f);
            objects.draw_after_player[i] = player->GetBottomCollisionY() < objects.ys[i] + object_quads_info.draw_order_offset_y[objects.quad_indexes[i]];
        } else {
            objects.opacities[i] = min(objects.opacities[i] + (*dt) * 200, 255.f);
        }
    }
}

void Map::DestroyTextures() {
    SDL_DestroyTexture(static_saved_drawn_data);
    SDL_DestroyTexture(texture);
}