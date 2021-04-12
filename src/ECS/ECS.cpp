#include "ECS.h"
#include "../Map.h"
#include "../Player.h"
#include "../Enemies.h"


void ECS::AddEntity(Entity* e) {

    if (! e) {
        print("Entity is null pointer!");
        return;
    }

    if (! e->asset || ! *(e->asset) ) {
        print("Asset is null pointer! %d", e->asset);
        return;
    }

    entities.push_back(e);
    draw_order_indexes.push_back(draw_order_indexes.size());

}

void ECS::Draw() {

    // bubble sort for draw order

    for (int _ = 0; _ < draw_order_indexes.size(); _ ++) {

        bool has_swapped = false;
        for (int j = 0; j < draw_order_indexes.size() - _ - 1; j ++) {

            // indexes and names of enemies
            int i1 = draw_order_indexes[j];
            int i2 = draw_order_indexes[j+1];

            // For draw order we use the collision box because the objects' collision box
            // always includes the bottom of the object (nature of topdown game). This
            // might change later.

            float e1_y = entities[i1]->y + (*(entities[i1]->asset))->movement_box->y + (*(entities[i1]->asset))->movement_box->h;
            float e2_y = entities[i2]->y + (*(entities[i2]->asset))->movement_box->y + (*(entities[i2]->asset))->movement_box->h;

            if (e1_y > e2_y) {
                draw_order_indexes[j]   = i2;
                draw_order_indexes[j+1] = i1;
                has_swapped = true;
            }
        }
        // If you haven't swapped any items, then the list is sorted, so no need to continue checking.
        if (! has_swapped) break;
    }

    for (unsigned int i = 0; i < draw_order_indexes.size(); i++) {
        entities[draw_order_indexes[i]]->Draw();
    }
}

void ECS::Update() {
    for (unsigned int i = 0; i < draw_order_indexes.size(); i++) {
        //entities[i]->Update();
    }
}

