#include "ECS.h"
#include "../Map.h"
#include "../Player.h"
#include "../Enemies.h"

void ECS::Init() {
    for (int i = 0; i < MAX_ENTITIES; i++) {
        entities[i] = NULL;
    }
}

void ECS::AddEntity(Entity* e) {

    if (num_active_entities == MAX_ENTITIES) {
        print("Too many entities!");
        return;
    }

    if (! e) {
        print("Entity is null pointer!");
        return;
    }

    if (! e->asset || ! *(e->asset) ) {
        print("Asset is null pointer! %d", e->asset);
        return;
    }

    entities[num_active_entities] = e;
    num_active_entities++;
}

void ECS::Draw() {

    // bubble sort for draw order

    int num_not_null = 0;
    for (int i = 0; i < MAX_ENTITIES; i++) {

        bool has_swapped = false;
        for (int j = 0; j < MAX_ENTITIES - i - 1; j++) {

            if (entities[j+1] == NULL) continue;
            // swap the null entity and the other entity here before we try to define e1_y and e2_y (if we try with NULL we'll get a seg fault)
            if (entities[j] == NULL) {

                entities[j] = entities[j+1];
                entities[j+1] = NULL;
                has_swapped = true;

                continue;
            }

            // For draw order we use the collision box because the objects' collision box
            // always includes the bottom of the object (nature of topdown game). This
            // might change later.
            float e1_y = entities[j]->y + (*(entities[j]->asset))->movement_box->y + (*(entities[j]->asset))->movement_box->h;
            float e2_y = entities[j+1]->y + (*(entities[j+1]->asset))->movement_box->y + (*(entities[j+1]->asset))->movement_box->h;

            if (e1_y > e2_y) {
                Entity* temp = entities[j];
                entities[j] = entities[j+1];
                entities[j+1] = temp;
                has_swapped = true;
            }
        }
        // If you haven't swapped any items, then the list is sorted, so no need to continue checking.
        if (! has_swapped) break;
    }

    for (int i = 0; i < num_active_entities; i++) {
        if (entities[i] == NULL) {
            print("%i", i);
            continue;
        }
        if (i == 30 and entities[i] != NULL) print("WOW THIS MUST BE PLAYER: %i", (int) entities[i]->type);
        entities[i]->Draw();
    }
}

void ECS::Update() {
    for (int i = num_active_entities - 1; i >= 0; i--) {
        if (entities[i]->should_delete) {
            entities[i] = NULL;
            num_active_entities--;
        }
    }
}

