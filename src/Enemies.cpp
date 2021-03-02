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
    for (int i = 0; i < 1; i ++) {
        AddBarrel();
    }
}

void Enemies::DrawEnemy(int id) {
    RenderCopy(g_window.rdr, barrel_asset->texture, & barrels[id].anim.quad, barrels[id].x, barrels[id].y);
}

void Enemies::Update() {
    for (auto & barrel_iter : barrels) {
        int id = barrel_iter.first;

        bool finished_animation_loop = UpdateAnimation(& barrels[id].anim, barrel_asset);

        // If in range of player and still idle, then get aggravated.
        if (pyth_s(player->GetDrawCenterX(), player->GetDrawCenterY(), barrels[id].x + barrel_asset->frame_width / 2, barrels[id].y + barrel_asset->frame_height / 2) < barrel_range*barrel_range && barrels[id].anim.name == "Idle") {
            barrels[id].aggravated = true;
            SetAnimation(& barrels[id].anim, barrel_asset, "Opening");
        }

        if (barrels[id].anim.name == "Opening" && finished_animation_loop) {
            SetAnimation(& barrels[id].anim, barrel_asset, "Attack");
        }

    }
}

void Enemies::AddBarrel() {
    int x = random(0, 500); int y = random(0, 500);
    int id = ecs->AddEntity(ENEMY_TYPE, x, y, & barrel_asset);

    barrels.insert(  std::pair<int, Barrel>(id, {
        x, y, false, {}
    } ));

    SetAnimation(& barrels[id].anim, barrel_asset, "Idle");
}