#pragma once

#include <vector>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "utils/LoadImage.hpp"
#include "utils/CurrentAnimationData.hpp"
#include "utils/ExtraCollisionInfo.hpp"
#include "GlobalWindowData.hpp"

// struct AnimationsData {
//     std::map<std::string, int> names;
//     std::vector<int> num_frames;
//     std::vector<float> speeds;
//     std::vector<int> offsets;
// };

enum EnemyType {
    SPIDER
};

struct EnemiesData {
    std::vector<float> xs;
    std::vector<float> ys;
    std::vector<EnemyType> enemy_types;
};

class Enemies {
public:
    void CreateTextures();
    void GiveDelta(float* _dt);
    void Draw();
    void Update();
private:
    float* dt;

    EnemiesData enemies_data = {{50}, {50}, {SPIDER}};


    std::map<EnemyType, ExtraCollisionInfo> extra_collision_info = {{SPIDER, {9, 24, 14, 9}}};
    std::map<EnemyType, AnimationsData> enemies_animations_data = {
        {
            SPIDER,
            {
                32, 32,
                {{"idle",0}, {"running",1}},
                { 4,      6       },
                { 0.3,    0.1     },
                { 0,      4       }
            }
        }
    };

    std::map<EnemyType, SDL_Texture*> textures;
};