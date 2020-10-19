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


struct SOA_CurrAnimations {
    std::vector<std::string> names;
    std::vector<float>       ticks;
    std::vector<int>         cur_frames;
    std::map<int, int>       id_to_index;
};


struct Enemies {
    void CreateTextures();
    void GiveDeltaMapECSPlayer(float* _dt, Map* _map, ECS* _ecs, Player* _player);
    void CreateEnemies();
    void DrawEnemy(int id);
    void Update();


    float*  dt;
    Map*    map;
    ECS*    ecs;
    Player* player;

    int activation_distance = 50;
    int deactivation_distance = 80;
    SOA_CurrAnimations cur_animations;

    SDL_Texture* spider_texture;
};