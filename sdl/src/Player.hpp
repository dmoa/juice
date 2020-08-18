#pragma once

#include <string>
#include <map>
#define ROOT2 1.41421356237;

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "GlobalWindowData.hpp"

#include "CurrentAnimationData.hpp"
#include "AnimationsData.hpp"

class Player {
public:
    void LoadTexture();
    void GiveDT(float* _dt);
    void Draw();
    void Update();
    void AnimationUpdate();
    void SetAnimationIfShould(std::string name);
    void DestroyTexture();
private:
    float* dt;

    float x = 5;
    float y = 5;
    float current_xv = 0;
    float current_yv = 0;
    int   v = 50;

    AnimationsData animations_data = {
        {{"idle",0}, {"running",1}},
        { 4,      6       },
        { 0.3,    0.1     },
        { 0,      4       }
    };

    CurrentAnimationData current_animation = {"idle", 0, 0, 0, animations_data.num_frames[0], animations_data.speeds[0]};

    SDL_Rect     current_quad;
    SDL_Rect     positional_quad;
    SDL_Texture* texture;
    SDL_RendererFlip is_flipped = SDL_FLIP_NONE;
};