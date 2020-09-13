#include "Map.hpp"
#include "Player.hpp"
#include "objects/DrawObjects.hpp"

void Map::LoadTexture() {
    texture = IMG_LoadTexture(global_window_data.rdr, "assets/tileset.png");
    if (!texture) SDL_Log("tileset.png not found");
}

void Map::ReloadTilesetTexture() {
    SDL_DestroyTexture(texture);
    LoadTexture();
}

void Map::GivePlayerDeltaDrawObjects(Player* _player, float* _dt, DrawObjects* _draw_objects) {
    player = _player;
    dt = _dt;
    draw_objects = _draw_objects;
};

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

    // TREES, LOGS AND STONES

    int x;
    int y;
    for (int i = 0; i < 100; i++) {
        x = random(tile_length, GetMapWidth() - tile_length * 2);
        y = random(tile_length, GetMapHeight() - tile_length * 3);
        int index = AddObjectIfPossible(x, y, TREE1);
        if (index != -1) object_opacities[index] = 255.f;
    }

    //AddObjectIfPossible(150, 150, TREE1);

    SDL_SetRenderTarget(global_window_data.rdr, NULL);
}

void Map::CreateCollisionBoxes() {

    // EDGE WATER TILES

    // top left to top bottom
    collision_boxes.xs.push_back(0);
    collision_boxes.ys.push_back(0);
    collision_boxes.ws.push_back(tile_length);
    collision_boxes.hs.push_back((tiles_high - 1) * tile_length);

    // top left to top right
    collision_boxes.xs.push_back(tile_length);
    collision_boxes.ys.push_back(0);
    collision_boxes.ws.push_back((tiles_wide - 1) * tile_length);
    collision_boxes.hs.push_back(tile_length);

    // top right to bottom right
    collision_boxes.xs.push_back((tiles_wide - 1) * tile_length);
    collision_boxes.ys.push_back(tile_length);
    collision_boxes.ws.push_back(tile_length);
    collision_boxes.hs.push_back((tiles_high - 1) * tile_length);

    // bottom left to bottom right
    collision_boxes.xs.push_back(0);
    collision_boxes.ys.push_back((tiles_high - 1) * tile_length);
    collision_boxes.ws.push_back((tiles_wide - 1) * tile_length);
    collision_boxes.hs.push_back(tile_length);
}

void Map::DrawBase() {
    SDL_RenderCopy(global_window_data.rdr, static_saved_drawn_data, NULL, NULL);
}

void Map::DrawObject(float x, float y, OBJECT_NAMES name, int id) {
        int i = name;
        SDL_Rect quad = {QUADS_INFO.xs[i], QUADS_INFO.ys[i], OBJECTS_QUAD_DIMENSIONS.ws[i], OBJECTS_QUAD_DIMENSIONS.hs[i]};
        SDL_Rect pos = {x, y, OBJECTS_QUAD_DIMENSIONS.ws[i], OBJECTS_QUAD_DIMENSIONS.hs[i]};
        SDL_RenderCopy(global_window_data.rdr, texture, & quad, & pos);
    }


void Map::Update() {
    for (unsigned int i = 0; i < draw_objects->objects.xs.size(); i++) {
        if (pyth(draw_objects->objects.xs[i] + OBJECTS_QUAD_DIMENSIONS.ws[draw_objects->objects.names[i]] / 2, draw_objects->objects.ys[i] + OBJECTS_QUAD_DIMENSIONS.hs[draw_objects->objects.names[i]] / 2, player->GetCenterX(), player->GetCenterY()) < opacity_distance) {
            object_opacities[draw_objects->objects.ids[i]] = max(object_opacities[draw_objects->objects.ids[i]] - (*dt) * 500, 130.f);
        } else {
            object_opacities[draw_objects->objects.ids[i]] = min(object_opacities[draw_objects->objects.ids[i]] + (*dt) * 200, 255.f);
        }
    }
}

void Map::DestroyTextures() {
    SDL_DestroyTexture(static_saved_drawn_data);
    SDL_DestroyTexture(texture);
}

int Map::AddObjectIfPossible(int x, int y, OBJECT_NAMES name) {
    for (unsigned int i = 0; i < draw_objects->objects.ys.size(); i++) {
        if (AABB(x, y, OBJECTS_QUAD_DIMENSIONS.ws[name], OBJECTS_QUAD_DIMENSIONS.hs[name], draw_objects->objects.xs[i], draw_objects->objects.ys[i], OBJECTS_QUAD_DIMENSIONS.ws[draw_objects->objects.names[i]], OBJECTS_QUAD_DIMENSIONS.hs[draw_objects->objects.names[i]])) {
            return -1;
        }
    }
    return draw_objects->AddObject(x, y, name, MAP_TYPE, -1);
}