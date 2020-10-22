#include "ECS.hpp"
#include "../Map.hpp"
#include "../Player.hpp"

void ECS::GiveMapPlayerEnemies(Map* _map, Player* _player, Enemies* _enemies) {
    map = _map;
    player = _player;
    enemies = _enemies;
}

int ECS::AddEntity(float x, float y, ENTITY_NAME name, ENTITY_TYPE type) {

    entities.push_back({x, y, name});
    entity_types.push_back(type);
    draw_order_indexes.push_back(entities.size() - 1);

    return entities.size() - 1;
}

void ECS::Draw() {

    // bubble sort for draw order

    for (int _ = 0; _ < draw_order_indexes.size(); _ ++) {
        for (int j = 0; j < draw_order_indexes.size() - _ - 1; j ++) {

            // indexes and names of enemies
            int i1 = draw_order_indexes[j];
            int i2 = draw_order_indexes[j+1];
            int name1 = entities[i1].name;
            int name2 = entities[i2].name;

            if (entities[i1].y + ENTITY_COLLISION_DATA[name1].y + ENTITY_COLLISION_DATA[name1].h > entities[i2].y + ENTITY_COLLISION_DATA[name2].y + ENTITY_COLLISION_DATA[name2].h) {

                draw_order_indexes[j]   = i2;
                draw_order_indexes[j+1] = i1;
            }
        }
    }

    for (unsigned int i = 0; i < draw_order_indexes.size(); i++) {
        int j = draw_order_indexes[i];

        switch (entity_types[j]) {
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
                SDL_Log("Entity not being drawn!, x: %i, y: %i, name: %i, id: %i, type: %i", entities[j].x, entities[j].y, (int) entities[j].name, j, (int) entity_types[j]);
                break;
        }

    }
}