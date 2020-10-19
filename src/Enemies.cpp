#include "Enemies.hpp"

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

        cur_animations.names.push_back("attack");
        cur_animations.cur_frames.push_back(0);
        cur_animations.ticks.push_back(0);
        id_to_index[id] = cur_animations.ticks.size() - 1;
        is_right.push_back(false);
    }
}

void Enemies::DrawEnemy(int id) {

    int i = id_to_index[id];

    SDL_Rect quad;
    SDL_Rect pos;

    UpdateAnimationQuad(cur_animations.names[i], cur_animations.cur_frames[i], SPIDER, & quad.x, & quad.y);
    quad.w = pos.w = ENTITY_QUAD_DIMENSIONS.ws[ecs->entities.names[id]];
    quad.h = pos.h = ENTITY_QUAD_DIMENSIONS.hs[ecs->entities.names[id]];
    pos.x = ecs->entities.xs[id];
    pos.y = ecs->entities.ys[id];

    SDL_RenderCopyEx(global_window_data.rdr, spider_texture, & quad, & pos, NULL, NULL, is_right[i] ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
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
    int distance_from_player_squared = pyth_s(ecs->entities.xs[id] + ENTITY_COLLISION_DATA.xs[ecs->entities.names[id]] + ENTITY_COLLISION_DATA.ws[ecs->entities.names[id]] / 2, ecs->entities.ys[id] + ENTITY_COLLISION_DATA.ys[ecs->entities.names[id]] + ENTITY_COLLISION_DATA.hs[ecs->entities.names[id]] / 2, player->GetCenterX(), player->GetCenterY());

    if (distance_from_player_squared < attack_distance*attack_distance) {
        SetAnimationIf(& cur_animations.names[j], "attack", & cur_animations.ticks[j], & cur_animations.cur_frames[j], ecs->entities.names[id]);
    }
    else if (distance_from_player_squared < activation_distance*activation_distance) {
        SetAnimationIf(& cur_animations.names[j], "running", & cur_animations.ticks[j], & cur_animations.cur_frames[j], ecs->entities.names[id]);
    }
    else if (distance_from_player_squared > deactivation_distance*deactivation_distance) {
        SetAnimationIf(& cur_animations.names[j], "idle", & cur_animations.ticks[j], & cur_animations.cur_frames[j], ecs->entities.names[id]);
    }

    AnimationTick(dt, & cur_animations.names[j], & cur_animations.ticks[j], & cur_animations.cur_frames[j], ecs->entities.names[id]);
}

void Enemies::UpdateEnemyMovement(int id, int j) {
    if (cur_animations.names[j] == "running" || cur_animations.names[j] == "attack") {
        // Calculate xv and yv for enemy to follow player at a max speed and at the correct angle.

        float xv = player->GetCenterX() - (ecs->entities.xs[id] + ENTITY_COLLISION_DATA.xs[ecs->entities.names[id]] + ENTITY_COLLISION_DATA.ws[ecs->entities.names[id]] / 2);
        float yv = player->GetCenterY() - (ecs->entities.ys[id] + ENTITY_COLLISION_DATA.ys[ecs->entities.names[id]] + ENTITY_COLLISION_DATA.hs[ecs->entities.names[id]] / 2);

        is_right[j] = xv > 0 ? true : false;

        if (cur_animations.names[j] == "running") { // To avoid vibration when next to the player.

            float cap_v = 50 / sqrt(xv*xv + yv*yv);

            xv *= cap_v;
            yv *= cap_v;


            ecs->entities.xs[id] += xv * (*dt);
            ecs->entities.ys[id] += yv * (*dt);
        }
    }
}
