#include "Enemies.h"

void Enemies::GivePointers(ECS* _ecs) {
    ecs = _ecs;
}

void Enemies::LoadAssets() {
    barrel_asset = LoadAsset_Ase_Animated("assets/barrel.ase");
}

void Enemies::DestroyAssets() {
    DestroyAsset_Ase_Animated(barrel_asset);
}

void Enemies::InitAllEnemies() {
        AddBarrel();AddBarrel();AddBarrel();AddBarrel();AddBarrel();AddBarrel();AddBarrel();AddBarrel();AddBarrel();AddBarrel();AddBarrel();AddBarrel();AddBarrel();AddBarrel();AddBarrel();AddBarrel();AddBarrel();AddBarrel();AddBarrel();AddBarrel();
}

void Enemies::DrawEnemy(int id) {
    RenderCopy(g_window.rdr, barrel_asset->texture, & barrels[id].anim.quad, barrels[id].x, barrels[id].y);
}

void Enemies::Update() {
    for (auto & it : barrels) {
        Barrel b = it.second;

        UpdateAnimation(& b.anim, barrel_asset);
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