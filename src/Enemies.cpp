#include "Enemies.h"

void Enemies::GivePointers(ECS* _ecs, Player* _player) {
    ecs = _ecs;
    player = _player;
}

void Enemies::LoadAssets() {
    barrel_asset = LoadAsset_Ase_Animated("assets/barrel.ase");
}

void Enemies::DestroyAssets() {
    DestroyAsset_Ase_Animated(barrel_asset);
}

void Enemies::InitAllEnemies() {
    for (int i = 0; i < NUM_ENEMIES; i++) {

        barrels[i].x = random(0, 500); barrels[i].y = random(0, 500);
        Animation_Set(& barrels[i].anim, barrel_asset, "Idle");
        barrels[i].asset = (Asset_Ase**) & barrel_asset;

        ecs->AddEntity(& barrels[i]);
    }
}

void Enemies::Update() {

    for (int i = 0; i < NUM_ENEMIES; i++) {

        Barrel* b = & barrels[i];

        bool finished_animation_loop = Animation_Update(& b->anim, barrel_asset);

        // If in range of player and still idle, then get aggravated.
        if (pyth_s(player->GetDrawCenterX(), player->GetDrawCenterY(), b->x + barrel_asset->frame_width / 2, b->y + barrel_asset->frame_height / 2) < barrel_range*barrel_range) {

            b->aggravated = true;
            b->agg_timer = barrel_aggr_time;

            // If player enemy damage boxes collide (and for now it's just barrel so we can generalise) and if player is in front of enemy (logically in front of enemy means the player is below the enemy)
            if (AABB(*player->asset, barrel_asset, player->x, player->y, b->x, b->y) && player->y + (*player->asset)->movement_box->y + (*player->asset)->movement_box->h > b->y + barrel_asset->movement_box->y + barrel_asset->movement_box->h) {

                // If the attack_timer is not in use, activate it, otherwise, keep using it by counting down.
                if (b->attack_timer == -1) {
                    // The reason we don't do:
                    // b->attack_timer = barrel_attack_interval;
                    // is because we want the moment we are in range of the player to damage it, rather than waiting one cycle before damaging the player.
                    b->attack_timer = 0;
                }
                else {
                    b->attack_timer -= g_dt;
                    if (b->attack_timer < 0) {
                        b->attack_timer = b->anim.tick / 1000;
                        player->current_health -= barrel_damage;
                    }
                }

            }
        }
        else {
            b->agg_timer -= g_dt;
            if (b->agg_timer < 0) {
                b->aggravated = false;
                b->attack_timer = -1;
            }
        }

        if (strequal(b->anim.name, "Opening") && finished_animation_loop) Animation_Set(& b->anim, barrel_asset, "Attack");
        if (b->aggravated && strequal(b->anim.name, "Idle")) Animation_Set(& b->anim, barrel_asset, "Opening");
        if (! b->aggravated) Animation_SetIf(& b->anim, barrel_asset, "Idle");

    }
}

void Barrel::Draw() {
    DrawAnimatedEntity(this, & anim);
}