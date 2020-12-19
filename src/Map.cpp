#include "Map.h"
#include "Player.h"
#include "ECS/ECS.h"

void Map::LoadTexture() {
    texture = LoadImage(g_window.rdr, "assets/tileset.png");
}

void Map::ReloadTilesetTexture() {
    SDL_DestroyTexture(texture);
    LoadTexture();
}

void Map::PassPointers(Player* _player, float* _dt, ECS* _ecs) {
    player = _player;
    dt = _dt;
    ecs = _ecs;
};

void Map::CreateMapTexture() {
    SDL_SetRenderTarget(g_window.rdr, static_saved_drawn_data);

    SDL_Rect iter_quad = {0, 0, tile_length, tile_length};
    SDL_Rect iter_pos  = {0, 0, tile_length, tile_length};

    // GRASS TILES

    for (int i = 1; i < tiles_wide - 1; i++) {
        for (int j = 1; j < tiles_high - 1; j++) {
            iter_pos.x = i * tile_length;
            iter_pos.y = j * tile_length;
            iter_quad.x = (rand() % 5) * tile_length;
            SDL_RenderCopy(g_window.rdr, texture, & iter_quad, & iter_pos);
        }
    }

    // EDGE WATER TILES

    iter_quad.y = 16; // switching to row of water quads
    iter_quad.x = 48;

    iter_pos.x = iter_pos.y = 0;
    SDL_RenderCopy(g_window.rdr, texture, & iter_quad, & iter_pos);
    iter_pos.x = (tiles_wide - 1) * tile_length;
    SDL_RenderCopy(g_window.rdr, texture, & iter_quad, & iter_pos);
    iter_pos.x = 0;
    iter_pos.y = (tiles_high - 1) * tile_length;
    SDL_RenderCopy(g_window.rdr, texture, & iter_quad, & iter_pos);
    iter_pos.x = (tiles_wide - 1) * tile_length;
    SDL_RenderCopy(g_window.rdr, texture, & iter_quad, & iter_pos);

    iter_pos.y = 0;
    iter_quad.x = 80;
    for (int i = 1; i < tiles_wide - 1; i++) {
        iter_pos.x = i * tile_length;
        SDL_RenderCopy(g_window.rdr, texture, & iter_quad, & iter_pos);
    }

    iter_quad.x = 32;
    iter_pos.x = 0;
    for (int i = 1; i < tiles_high - 1; i++) {
        iter_pos.y = i * tile_length;
        SDL_RenderCopyEx(g_window.rdr, texture, & iter_quad, & iter_pos, NULL, NULL, SDL_FLIP_HORIZONTAL);
    }

    iter_pos.x = (tiles_wide - 1) * tile_length;
    for (int i = 1; i < tiles_high - 1; i++) {
        iter_pos.y = i * tile_length;
        SDL_RenderCopy(g_window.rdr, texture, & iter_quad, & iter_pos);
    }

    iter_quad.x = 80;
    iter_pos.y = (tiles_high - 1) * tile_length;
    for (int i = 1; i < tiles_wide - 1; i++) {
        iter_pos.x = i * tile_length;
        SDL_RenderCopyEx(g_window.rdr, texture, & iter_quad, & iter_pos, NULL, NULL, SDL_FLIP_VERTICAL);
    }

    // TREES, LOGS AND STONES

    int x;
    int y;
    for (int i = 0; i < 100; i++) {
        x = random(tile_length, GetMapWidth() - tile_length * 2);
        y = random(tile_length, GetMapHeight() - tile_length * 3);
        int entity_id = AddEntityIfPossible(x, y, (ENTITY_NAME) (rand() % NUM_MAP_ENTITY_TYPE + MAP_ENTITY_OFFSET)); // oddly specific, it's just the numerical value of all the map object enums
        if (entity_id != -1) object_opacities[entity_id] = 255.f;
    }

    SDL_SetRenderTarget(g_window.rdr, NULL);
}

void Map::CreateCollisionBoxes() {

    // EDGE WATER TILES

    // top left to top bottom
    collision_boxes.push_back({0, 0, tile_length, (tiles_high - 1) * tile_length});

    // top left to top right
    collision_boxes.push_back({tile_length, 0, (tiles_wide - 1) * tile_length, tile_length});

    // top right to bottom right
    collision_boxes.push_back({(tiles_wide - 1) * tile_length, tile_length, tile_length, (tiles_high - 1) * tile_length});

    // bottom left to bottom right
    collision_boxes.push_back({0, (tiles_high - 1) * tile_length, (tiles_wide - 1) * tile_length, tile_length});
}

void Map::DrawBase() {
    SDL_RenderCopy(g_window.rdr, static_saved_drawn_data, NULL, NULL);
}

void Map::DrawObject(int id) {
    ENTITY_NAME name = ecs->entities[id].name;

    SDL_Rect pos;
    SDL_Rect quad;

    pos.x = ecs->entities[id].x;
    pos.y = ecs->entities[id].y;

    quad.x = QUAD_DIMENSIONS[name].x;
    quad.y = QUAD_DIMENSIONS[name].y;

    quad.w = pos.w = QUAD_DIMENSIONS[name].w;
    quad.h = pos.h = QUAD_DIMENSIONS[name].h;

    SDL_SetTextureAlphaMod(texture, object_opacities[id]);
    SDL_RenderCopy(g_window.rdr, texture, & quad, & pos);
}


void Map::Update() {
    // info.second = opacity
    for (auto & info : object_opacities) {
        int id = info.first;

        if (pyth_s(ecs->entities[id].x + QUAD_DIMENSIONS[ecs->entities[id].name].w / 2, ecs->entities[id].y  + QUAD_DIMENSIONS[ecs->entities[id].name].h / 2, player->GetDrawCenterX(), player->GetDrawCenterY()) < opacity_distance*opacity_distance) {
            info.second = max(object_opacities[id] - (*dt) * 500, 130.f);
        } else {
            info.second = min(object_opacities[id] + (*dt) * 200, 255.f);
        }
    }
}

void Map::DestroyTextures() {
    SDL_DestroyTexture(static_saved_drawn_data);
    SDL_DestroyTexture(texture);
}

int Map::AddEntityIfPossible(int x, int y, ENTITY_NAME name) {
    for (unsigned int i = 0; i < ecs->entities.size(); i++) {
        if (AABB(x, y, QUAD_DIMENSIONS[name].w, QUAD_DIMENSIONS[name].h, ecs->entities[i].x, ecs->entities[i].y, QUAD_DIMENSIONS[ecs->entities[i].name].w, QUAD_DIMENSIONS[ecs->entities[i].name].h)) {
            return -1;
        }
    }
    return ecs->AddEntity(x, y, name, MAP_TYPE);
}