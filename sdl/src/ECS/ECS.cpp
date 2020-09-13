#include "ECS.hpp"
#include "../Map.hpp"
#include "../Player.hpp"

void ECS::GiveMapPlayerEnemies(Map* _map, Player* _player, Enemies* _enemies) {
    map = _map;
    player = _player;
    enemies = _enemies;
}

int ECS::AddEntity(float x, float y, ENTITY_NAME name, ENTITY_TYPE type, int id) {
    int i;

    for (i = 0; i < entities.xs.size(); i ++) {
        if (AABB(x, y, ENTITY_QUAD_DIMENSIONS.ws[name], ENTITY_QUAD_DIMENSIONS.hs[name], entities.xs[i], entities.ys[i], ENTITY_QUAD_DIMENSIONS.ws[entities.names[i]], ENTITY_QUAD_DIMENSIONS.hs[entities.names[i]]) && y + ENTITY_COLLISION_INFO.ys[name] + ENTITY_COLLISION_INFO.hs[name] < entities.ys[i] + ENTITY_COLLISION_INFO.ys[entities.names[i]] + ENTITY_COLLISION_INFO.hs[entities.names[i]]) {
            break;
        }
    }


    entities.xs.insert(entities.xs.begin() + i, x);
    entities.ys.insert(entities.ys.begin() + i, y);
    entities.names.insert(entities.names.begin() + i, name);
    entities.types.insert(entities.types.begin() + i, type);

    // if no id has been given, it's a new object, and we can generate a unique id.
    if (id == -1) id = i;
    entities.ids.insert(entities.ids.begin() + i, id);

    return id;
}

// Sorting for the draw order, but not bothering to sort entities that don't move with each other.
void ECS::Sort() {

    // reordering entities
    SOAEntities _old_entities = entities;
    entities = SOAEntities();
    for (unsigned int i = 0; i < _old_entities.xs.size(); i ++) {
        AddEntity(_old_entities.xs[i], _old_entities.ys[i], _old_entities.names[i], _old_entities.types[i], _old_entities.ids[i]);
    }

    // remapping keys
    for (unsigned int i = 0; i < entities.xs.size(); i ++) {
        find_entities[entities.ids[i]] = i;
    }
}

void ECS::Draw() {
    for (unsigned int i = 0; i < entities.xs.size(); i++) {

        ENTITY_NAME name = entities.names[i];

        switch (entities.types[i]) {
            case PLAYER_TYPE:
                player->Draw();
                break;
            case MAP_TYPE:
                map->DrawObject(entities.xs[i], entities.ys[i], name, entities.ids[i]);
                break;
            default:
                SDL_Log("Entity not being drawn!, x: %i, y: %i, name: %i, id: %i, type: %i", entities.xs[i], entities.ys[i], (int) entities.names[i], (int) entities.ids[i], (int) entities.types[i]);
                break;
        }

    }
}