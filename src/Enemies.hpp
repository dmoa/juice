#pragma once

#include <vector>
#include <map>
#include <string>

#include "sdl.h"

#include "utils/random.hpp"
#include "utils/LoadImage.hpp"
#include "utils/pyth_s.hpp"
#include "GlobalWindowData.hpp"

#include "Map.hpp"
#include "Player.hpp"

#include "ECS/ECS.hpp"




struct Enemies {
    void CreateTextures();
    void GiveDeltaMapECSPlayer(float* _dt, Map* _map, ECS* _ecs, Player* _player);
    void CreateEnemies();
    void DrawEnemy(int id);
    void Update();
    void UpdateEnemyAnimation(int id, int j);
    void UpdateEnemyMovement(int id, int j);


    float*  dt;
    Map*    map;
    ECS*    ecs;
    Player* player;

    const int activation_distance   = 50;
    const int deactivation_distance = 80;
    const int attack_distance       = 25;

    // Components on top of ECS for enemy only

    std::map<int, int> id_to_index;
    std::vector<bool>  is_right; // direction
    std::vector<CurrAnimation> cur_anim;



    SDL_Texture* spider_texture;
};