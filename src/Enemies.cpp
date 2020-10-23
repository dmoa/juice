#include "Enemies.h"
#include "Player.h"
#include "Map.h"
#include "ECS/ECS.h"

void Enemies::CreateTextures() {
   spider_texture = LoadImage(global_window_data.rdr, "assets/enemies/spider.png");
}

void Enemies::GiveDeltaMapECSPlayer(float* _dt, Map* _map, ECS* _ecs, Player* _player) {
    dt     = _dt;
    map    = _map;
    ecs    = _ecs;
    player = _player;
}

void Enemies::CreateEnemies() {
    for (int i = 0; i < 100; i ++) {
        int id = ecs->AddEntity(random(50, map->map_width - 100), random(50, map->map_height - 100), SPIDER, ENEMY_TYPE);

        float tick = float(random(0, 200)) / 1000;
        cur_anim.push_back({IDLE, tick, 0});
        id_to_index[id] = cur_anim.size() - 1;
        is_right.push_back(false);
    }
}

void Enemies::DrawEnemy(int id) {
    int j = id_to_index[id];

    SDL_Rect quad;
    SDL_Rect pos;

    UpdateAnimationQuad(ecs->entities[id].name, & cur_anim[j], & quad.x, & quad.y);
    quad.w = pos.w = QUAD_DIMENSIONS[ecs->entities[id].name].w;
    quad.h = pos.h = QUAD_DIMENSIONS[ecs->entities[id].name].h;
    pos.x = ecs->entities[id].x;
    pos.y = ecs->entities[id].y;

    SDL_RenderCopyEx(global_window_data.rdr, spider_texture, & quad, & pos, NULL, NULL, is_right[j] ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
}

void Enemies::Update() {
    // info.first  -> entity id
    // info.second -> index for additional components stored in Enemies.

    for (auto & info : id_to_index) {
        UpdateEnemyAnimation(info.first, info.second);
        UpdateEnemyMovement(info.first, info.second);
    }

}

void Enemies::UpdateEnemyAnimation(int id, int j) {
    int distance_from_player_squared = pyth_s(ecs->GetCenterX(id), ecs->GetCenterY(id), ecs->GetCenterX(player->id), ecs->GetCenterY(player->id));

    if (distance_from_player_squared < attack_distance*attack_distance) {
        SetAnimationIf(ecs->entities[id].name, & cur_anim[j], ATTACK);
    }
    else if (distance_from_player_squared < activation_distance*activation_distance) {
        SetAnimationIf(ecs->entities[id].name, & cur_anim[j], RUN);
    }
    else if (distance_from_player_squared > deactivation_distance*deactivation_distance) {
        SetAnimationIf(ecs->entities[id].name, & cur_anim[j], IDLE);
    }


    AnimationTick(ecs->entities[id].name, & cur_anim[j], dt);
}

void Enemies::UpdateEnemyMovement(int id, int j) {
    if (cur_anim[j].type == RUN || cur_anim[j].type == ATTACK) {
        // Calculate xv and yv for enemy to follow player at a max speed and at the correct angle.

        float xv = ecs->GetCenterX(player->id) - ecs->GetCenterX(id);
        float yv = ecs->GetCenterY(player->id) - ecs->GetCenterY(id);

        is_right[j] = xv > 0 ? true : false;

        if (cur_anim[j].type == RUN) { // To avoid vibration when next to the player.

            float cap_v = 50 / sqrt(xv*xv + yv*yv);

            xv *= cap_v;
            yv *= cap_v;


            ecs->entities[id].x += xv * (*dt);
            ecs->entities[id].y += yv * (*dt);
        }
    }
}
