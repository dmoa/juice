#pragma once

#include <vector>
#include <map>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "utils/random.hpp"
#include "utils/LoadImage.hpp"
#include "utils/ExtraCollisionInfo.hpp"
#include "utils/AnimationsData.hpp"
#include "GlobalWindowData.hpp"

#include "Map.hpp"

enum EnemyType {
    SPIDER
};

struct EnemiesData {
    std::vector<EnemyType> types;
    std::vector<float> xs;
    std::vector<float> ys;
    std::vector<std::string> current_animations;
    std::vector<float> animation_timers;
    std::vector<int>   animation_indexes;
};

class Enemies {
public:
    void CreateTextures();
    void GiveDeltaMap(float* _dt, Map* _map);
    inline void AddEnemy(EnemyType type, float x, float y, std::string cur_animation);
    void CreateEnemies();
    void Draw();
    void Update();
private:
    float* dt;
    Map*   map;

    EnemiesData enemies_data;


    std::map<EnemyType, ExtraCollisionInfo> extra_collision_info = {{SPIDER, {9, 24, 14, 9}}};
    std::map<EnemyType, AnimationsData> enemies_animations_data = {
        {
            SPIDER,
            {
                32, 32,
                {{"idle",0}, {"running",1}},
                { 5,      6       },
                { 0.2,    0.1     },
                { 0,      1       }
            }
        }
    };

    std::map<EnemyType, SDL_Texture*> textures;
};