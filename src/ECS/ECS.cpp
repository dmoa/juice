#include "ECS.h"
#include "../Map.h"
#include "../Player.h"
#include "../Enemies.h"

void ECS::GiveMapPlayerEnemies(Map* _map, Player* _player, Enemies* _enemies) {
    map = _map;
    player = _player;
    enemies = _enemies;
}

int ECS::AddEntity(ENTITY_NAME name, ENTITY_TYPE type, float x, float y, Asset_Ase* asset) {

    int id = entities.size();

    entities[id] = {name, type, x, y, NULL};
    draw_order_indexes.push_back(id);

    return id;
}

void ECS::PopEntity(int id) {

    switch (entities[id].type) {

        case ENEMY_TYPE:
            enemies->enemies.erase(id);
            break;

        default: break;
    }
    entities.erase(id);
    draw_order_indexes.erase(std::remove(draw_order_indexes.begin(), draw_order_indexes.end(), id), draw_order_indexes.end());
}

void ECS::Draw() {

    // bubble sort for draw order

    for (int _ = 0; _ < draw_order_indexes.size(); _ ++) {

        bool has_swapped = false;
        for (int j = 0; j < draw_order_indexes.size() - _ - 1; j ++) {

            // indexes and names of enemies
            int i1 = draw_order_indexes[j];
            int i2 = draw_order_indexes[j+1];
            int name1 = entities[i1].name;
            int name2 = entities[i2].name;

            // For draw order we use the collision box because the objects' collision box
            // always includes the bottom of the object (nature of topdown game). This
            // might change later.
            if (entities[i1].asset== NULL || entities[i2].asset== NULL) break;
            if (entities[i1].asset->collision_box == NULL || entities[i2].asset->collision_box == NULL) break;

            if (entities[i1].y + entities[i1].asset->collision_box->y + entities[i1].asset->collision_box->h > entities[i2].y + entities[i2].asset->collision_box->y + entities[i2].asset->collision_box->h) {
                draw_order_indexes[j]   = i2;
                draw_order_indexes[j+1] = i1;
                has_swapped = true;
            }
        }
        // If you haven't swapped any items, then the list is sorted, so no need to continue checking.
        if (! has_swapped) {
            break;
        }
    }

    for (unsigned int i = 0; i < draw_order_indexes.size(); i++) {
        int j = draw_order_indexes[i];

        switch (entities[j].type) {
            case PLAYER_TYPE:
                player->Draw();
                break;
            case MAP_TYPE:
                map->DrawObject(j);
                break;
            case ENEMY_TYPE:
                enemies->DrawEnemy(j);
                break;
            default:
                SDL_Log("Entity not being drawn!, x: %i, y: %i, name: %i, id: %i, type: %i", entities[j].x, entities[j].y, (int) entities[j].name, j, (int) entities[j].type);
                break;
        }

    }
}