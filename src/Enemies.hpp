#pragma once

#include <vector>
#include <map>
#include <string>

#include "sdl.h"

#include "utils/random.hpp"
#include "utils/LoadImage.hpp"
#include "GlobalWindowData.hpp"

#include "Map.hpp"

#include "ECS/ECS.hpp"


struct SOA_CurrAnimations {
    std::vector<std::string> names;
    std::vector<float>       ticks;
    std::vector<int>         cur_frames;
    std::map<int, int>       id_to_index;
};


class Enemies {
public:
    void CreateTextures();
    void GiveDeltaMapECS(float* _dt, Map* _map, ECS* _ecs);
    void CreateEnemies();
    void DrawEnemy(int id);
    void Update();
private:
    float* dt;
    Map*   map;
    ECS*   ecs;


    SOA_CurrAnimations cur_animations;

    SDL_Texture* spider_texture;
};