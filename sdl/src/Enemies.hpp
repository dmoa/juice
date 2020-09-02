#pragma once

#include <vector>
#include <map>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "utils/LoadImage.hpp"
//#include "utils/CurrentAnimationsData.hpp"
#include "utils/ExtraCollisionInfo.hpp"
#include "utils/AnimationsData.hpp"
#include "GlobalWindowData.hpp"

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
    void GiveDelta(float* _dt);
    void Draw();
    void Update();
private:
    float* dt;

    EnemiesData enemies_data = {{SPIDER}, {50}, {50}, {"idle"}, {0}, {0}};


    std::map<EnemyType, ExtraCollisionInfo> extra_collision_info = {{SPIDER, {9, 24, 14, 9}}};
    std::map<EnemyType, AnimationsData> enemies_animations_data = {
        {
            SPIDER,
            {
                32, 32,
                {{"idle",0}, {"running",1}},
                { 4,      6       },
                { 0.2,    0.1     },
                { 0,      4       }
            }
        }
    };

    std::map<EnemyType, SDL_Texture*> textures;
};