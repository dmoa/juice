#pragma once

#include <string>

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
    void SetAnimationIfShould(std::string name);
private:
    float* dt;

    float x = 5;
    float y = 5;
    int xv = 50;
    int yv = 50;

    AnimationsData animations_data = {
        {"idle", "running"},
        { 4,      6       },
        { 0.3,    0.1     }
    };

    CurrentAnimationData current_animation = {"idle", 0, 0, 0, & animations_data.num_frames[0], & animations_data.speeds[0]};

    SDL_Rect current_quad;
    SDL_Rect positional_quad;
    SDL_Texture* texture;
    SDL_RendererFlip is_flipped = SDL_FLIP_NONE;
};