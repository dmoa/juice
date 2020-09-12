#include "DrawObjects.hpp"
#include "../Map.hpp"
#include "../Player.hpp"

void DrawObjects::GiveMapPlayerEnemies(Map* _map, Player* _player, Enemies* _enemies) {
    map = _map;
    player = _player;
    enemies = _enemies;
}

int DrawObjects::AddObject(float x, float y, OBJECT_NAMES name, OBJECT_TYPES type, int id) {
    int i;

    for (i = 0; i < objects.xs.size(); i ++) {
        if (AABB(x, y, OBJECTS_QUAD_DIMENSIONS.ws[name], OBJECTS_QUAD_DIMENSIONS.hs[name], objects.xs[i], objects.ys[i], OBJECTS_QUAD_DIMENSIONS.ws[objects.names[i]], OBJECTS_QUAD_DIMENSIONS.hs[objects.names[i]])) {

            // i = 0
            // y is the tree, objects.ys[i] is the player
            if (y + OBJECTS_COLLISION_INFO.ys[name] + OBJECTS_COLLISION_INFO.hs[name] < objects.ys[i] + OBJECTS_COLLISION_INFO.ys[objects.names[i]] + OBJECTS_COLLISION_INFO.hs[objects.names[i]]) {
                break;
            }
        }
    }


// KEEP OBJECTS IN THE CORRECT PLACE, (MAYBE NEED LOOKUP STILL FOR WHEN OBJECTS ARE DELETED)
// KEEP VECTOR OF INTS, FOR THE CORRECT DRAW ORDER.    

    // // SDL_Log("%i", i);

    // objects.xs.insert(objects.xs.begin() + i, x);
    // objects.ys.insert(objects.ys.begin() + i, y);
    // objects.names.insert(objects.names.begin() + i, name);
    // objects.types.insert(objects.types.begin() + i, type);

    // // if no id has been given, it's a new object, and we can generate a unique id.
    // if (id == -1) id = i;
    // objects.ids.insert(objects.ids.begin() + i, id);

    // SDL_Log("id: %i index: %i", id, i);
    // find_objects[id] = i;
    // if (i < objects.xs.size() - 1) {
    //     objects.ids[i - 1] = i - 1;
    // }

//    SDL_Log("%i", id);
    return id;
}

// Sorting for the draw order, but not bothering to sort objects that don't move with each other.
void DrawObjects::Sort() {
    Objects _old_objects = objects;
    objects = Objects();
    find_objects.clear();

    for (unsigned int i = 0; i < _old_objects.xs.size(); i ++) {
        AddObject(_old_objects.xs[i], _old_objects.ys[i], _old_objects.names[i], _old_objects.types[i], _old_objects.ids[i]);
    }
}

void DrawObjects::Draw() {
    for (unsigned int i = 0; i < objects.xs.size(); i++) {

        OBJECT_NAMES name = objects.names[i];

        switch (objects.types[i]) {
            case PLAYER_TYPE:
                player->Draw();
                break;
            case MAP_TYPE:
                map->DrawObject(objects.xs[i], objects.ys[i], name);
                break;
        }

    }
}