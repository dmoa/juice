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
        SetAnimation(& barrels[i].anim, barrel_asset, "Idle");
        barrels[i].asset = (Asset_Ase**) & barrel_asset;

        ecs->AddEntity(& barrels[i]);
    }
}

void Enemies::Update() {

    for (int i = 0; i < NUM_ENEMIES; i++) {

        Barrel* b = & barrels[i];

        bool finished_animation_loop = UpdateAnimation(& b->anim, barrel_asset);

        // If in range of player and still idle, then get aggravated.
        if (pyth_s(player->GetDrawCenterX(), player->GetDrawCenterY(), b->x + barrel_asset->frame_width / 2, b->y + barrel_asset->frame_height / 2) < barrel_range*barrel_range) {
            b->aggravated = true;
            b->timer = barrel_aggr_time;
        }
        else {
            b->timer -= g_dt;
            if (b->timer < 0) b->aggravated = false;
        }

        if (b->anim.name == "Opening" && finished_animation_loop) SetAnimation(& b->anim, barrel_asset, "Attack");
        if (b->aggravated && b->anim.name == "Idle")         SetAnimation(& b->anim, barrel_asset, "Opening");
        if (! b->aggravated)                                      SetAnimationIf(& b->anim, barrel_asset, "Idle");

    }
}

void Barrel::Draw() {
    DrawAnimatedEntity(this, & anim);
}