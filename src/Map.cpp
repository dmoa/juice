#include "Map.h"
#include "Player.h"
#include "ECS/ECS.h"

void Map::LoadAssets() {
    texture = LoadAsset_IMG("assets/tileset.png");

    still_objects[0] = LoadAsset_Ase("assets/map/tree1.ase");
    still_objects[1] = LoadAsset_Ase("assets/map/tree2.ase");
    still_objects[2] = LoadAsset_Ase("assets/map/stone.ase");
    still_objects[3] = LoadAsset_Ase("assets/map/trunk.ase");
}

void Map::DestroyAssets() {
    SDL_DestroyTexture(texture);
    for (int i = 0; i < NUM_STILL_OBJECTS; i++) { DestroyAsset_Ase(still_objects[i]); }
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

    SDL_SetRenderTarget(g_window.rdr, NULL);

    // TREES, LOGS AND STONES
    // We don't add these objects to static_saved_drawn_data because
    // when the player gets to one of the objects the opacity changes,
    // so they have to be independently drawn.
    int x;
    int y;
    for (int i = 0; i < 100; i++) {
        x = random(tile_length, GetMapWidth() - tile_length * 2);
        y = random(tile_length, GetMapHeight() - tile_length * 3);
        int entity_id = AddEntityIfPossible(x, y, & still_objects[random(0, NUM_STILL_OBJECTS)]); // oddly specific, it's just the numerical value of all the map object enums
        if (entity_id != -1) object_opacities[entity_id] = 255.f;
    }

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
    Entity e = ecs->entities[id];
    Asset_Ase* a = *(e.asset);

    SDL_Rect pos = {e.x, e.y, a->frame_width, a->frame_height};

    SDL_SetTextureAlphaMod(a->texture, object_opacities[id]);
    SDL_RenderCopy(g_window.rdr, a->texture, NULL, & pos);
}


void Map::Update() {
    for (auto & info : object_opacities) {
        Entity e = ecs->entities[info.first];

        if (pyth_s(e.x + (*e.asset)->frame_width / 2, e.y + (*e.asset)->frame_height / 2, player->GetDrawCenterX(), player->GetDrawCenterY()) < opacity_distance*opacity_distance) {
            // info.first = entity id
            // info.second = entity opacity
            info.second = max(object_opacities[info.first] - (*dt) * 500, 130.f);
        }
        else {
            info.second = min(object_opacities[info.first] + (*dt) * 200, 255.f);
        }
    }
}

void Map::DestroyTextures() {
    SDL_DestroyTexture(static_saved_drawn_data);
    SDL_DestroyTexture(texture);
}

int Map::AddEntityIfPossible(int x, int y, Asset_Ase** asset) {
    for (unsigned int i = 0; i < ecs->entities.size(); i++) {
        if (AABB(x, y, (*asset)->frame_width, (*asset)->frame_height, ecs->entities[i].x, ecs->entities[i].y, (*ecs->entities[i].asset)->frame_width, (*ecs->entities[i].asset)->frame_height)) {
            return -1;
        }
    }
    return ecs->AddEntity(MAP_TYPE, x, y, asset);
}