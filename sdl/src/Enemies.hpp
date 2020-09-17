#pragma once

#include <vector>
#include <map>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "utils/random.hpp"
#include "utils/LoadImage.hpp"
// #include "utils/AnimationsData.hpp"
#include "GlobalWindowData.hpp"

#include "Map.hpp"

#include "ECS/ECS.hpp"

class Enemies {
public:
    void CreateTextures();
    void GiveDeltaMap(float* _dt, Map* _map);
    void CreateEnemies();
    void DrawEnemy(float x, float y, int id);
    void Update();
private:
    float* dt;
    Map*   map;

    // std::map<EntityType, AnimationsData> enemies_animations_data = {
    //     {
    //         SPIDER,
    //         {
    //             32, 32,
    //             {{"idle",0}, {"running",1}},
    //             { 5,      6       },
    //             { 0.2,    0.1     },
    //             { 0,      1       }
    //         }
    //     }
    // };

    //std::map<EnemyType, SDL_Texture*> textures;
};