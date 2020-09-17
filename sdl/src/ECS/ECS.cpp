#include "ECS.hpp"
#include "../Map.hpp"
#include "../Player.hpp"

void ECS::GiveMapPlayerEnemies(Map* _map, Player* _player, Enemies* _enemies) {
    map = _map;
    player = _player;
    enemies = _enemies;
}

int ECS::AddEntity(float x, float y, ENTITY_NAME name, ENTITY_TYPE type, int id) {

    entities.xs.push_back(x);
    entities.ys.push_back(y);
    entities.names.push_back(name);
    entities.types.push_back(type);

    if (ENTITY_ANIMATION_DATA.find(type) != ENTITY_ANIMATION_DATA.end()) {
        entities.animation_indexes.push_back(entities.animation_indexes.size() - 1);
        entities.current_animations.push_back(ENTITY_ANIMATION_DATA[type].begin()->first);
        entities.timers.push_back(0);
        entities.current_frames.push_back(0);
    } else {
        entities.animation_indexes.push_back(-1);
    }

    // if no id has been given, it's a new object, and we can generate a unique id.
    if (id == -1) id = entities.xs.size() - 1;
    entities.ids.push_back(id);

    draw_order_indexes.push_back(entities.xs.size() - 1);

    return id;
}

void ECS::SetEntityAnimation(int id, std::string name) {
    int i = entities.animation_indexes[id];

    entities.current_animations[i] = name;
    entities.timers = ENTITY_ANIMATION_DATA[entities.types[id]].timers[ENTITY_ANIMATION_DATA[entities.types[id]].animation_types[name]];
    entities.current_frames[i] = 1;
}

void ECS::UpdateAnimation() {
    for (int i = 0; i < animation_indexes.size(); i ++) {
        if (entities.animation_indexes[i] == -1) continue;

        int j = entities.animation_indexes[id];

        entities.timers[j] -= (*dt);

        if (entities.timers[j] < 0) {
            entities.timers[j] = ENTITY_ANIMATION_DATA[entities.types[id]].timers[ENTITY_ANIMATION_DATA[entities.types[id]].animation_types[name]];
            entities.current_frames[j] = (entities.current_frames[j] + 1) % ENTITY_ANIMATION_DATA[entities].num_frames[entities.current_animations[j]];
        }
    }
}

void ECS::Draw() {

    // bubble sort for draw order

    for (int _ = 0; _ < draw_order_indexes.size(); _ ++) {
        for (int j = 0; j < draw_order_indexes.size() - _ - 1; j ++) {

            // indexes and names of enemies
            int i1 = draw_order_indexes[j];
            int i2 = draw_order_indexes[j+1];
            int name1 = entities.names[i1];
            int name2 = entities.names[i2];

            if (entities.ys[i1] + ENTITY_COLLISION_DATA.ys[name1] + ENTITY_COLLISION_DATA.hs[name1] > entities.ys[i2] + ENTITY_COLLISION_DATA.ys[name2] + ENTITY_COLLISION_DATA.hs[name2]) {

                draw_order_indexes[j]   = i2;
                draw_order_indexes[j+1] = i1;
            }
        }
    }



    for (unsigned int i = 0; i < draw_order_indexes.size(); i++) {
        int j = draw_order_indexes[i];

        ENTITY_NAME name = entities.names[j];

        switch (entities.types[j]) {
            case PLAYER_TYPE:
                player->Draw();
                break;
            case MAP_TYPE:
                map->DrawObject(entities.xs[j], entities.ys[j], name, entities.ids[j]);
                break;
            default:
                SDL_Log("Entity not being drawn!, x: %i, y: %i, name: %i, id: %i, type: %i", entities.xs[j], entities.ys[j], (int) entities.names[j], (int) entities.ids[j], (int) entities.types[j]);
                break;
        }

    }
}