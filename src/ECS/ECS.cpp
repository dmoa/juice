#include "ECS.h"
#include "../Map.h"
#include "../Player.h"
#include "../Enemies.h"

void ECS::GiveMapPlayerEnemies(Map* _map, Player* _player, Enemies* _enemies) {
    map = _map;
    player = _player;
    enemies = _enemies;
}

int ECS::AddEntity(float x, float y, ENTITY_NAME name, ENTITY_TYPE type) {

    int id = entities.size();

    entities[id] = {x, y, name, type};
    draw_order_indexes.push_back(id);

    return id;
}

void ECS::PopEntity(int id) {
    entities.erase(id);
    draw_order_indexes.erase(std::remove(draw_order_indexes.begin(), draw_order_indexes.end(), id), draw_order_indexes.end());
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

            if (entities[i1].y + COLLISION_DATA[name1].y + COLLISION_DATA[name1].h > entities[i2].y + COLLISION_DATA[name2].y + COLLISION_DATA[name2].h) {

                draw_order_indexes[j]   = i2;
                draw_order_indexes[j+1] = i1;
            }
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