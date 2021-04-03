#include "ECS.h"
#include "../Map.h"
#include "../Player.h"
#include "../Enemies.h"

void ECS::GivePointers(Map* _map, Player* _player, Enemies* _enemies) {
    map = _map;
    player = _player;
    enemies = _enemies;
}

void ECS::AddEntity(Entity* entity) {

    // We don't check if entity is null because asset being
    // null is a much more common error to run into.
    if (! e->asset || ! *(e->asset) ) {
        print("Asset is null pointer");
        return;
    }

    draw_order_indexes.push_back(id);

}

// void ECS::PopEntity(int id) {
//     entities.erase(id);
//     draw_order_indexes.erase(std::remove(draw_order_indexes.begin(), draw_order_indexes.end(), id), draw_order_indexes.end());
// }

void ECS::Draw() {

    // bubble sort for draw order

    for (int _ = 0; _ < draw_order_indexes.size(); _ ++) {

        bool has_swapped = false;
        for (int j = 0; j < draw_order_indexes.size() - _ - 1; j ++) {

            // indexes and names of enemies
            int i1 = draw_order_indexes[j];
            int i2 = draw_order_indexes[j+1];

            if (entities[i1].asset == NULL || entities[i2].asset == NULL) { continue; }

            // For draw order we use the collision box because the objects' collision box
            // always includes the bottom of the object (nature of topdown game). This
            // might change later.

            if (entities[i1].y + (*entities[i1].asset)->movement_box->y + (*entities[i1].asset)->movement_box->h > entities[i2].y + (*entities[i2].asset)->movement_box->y + (*entities[i2].asset)->movement_box->h) {
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
        entities[i]->Draw(& entities[i]);
    }
}

void ECS::Update() {
    for (unsigned int i = 0; i < draw_order_indexes.size(); i++) {
        entities[i]->Update(& entities[i]);
    }
}