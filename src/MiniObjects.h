#pragma once

#include <map>

#include "sdl.h"
#include "Globals/All.h"
#include "utils/AssetLoader.h"

#include "ECS/Animation/UpdateAnimation.h"

#include "ECS/ECS.h"

struct Obj {
    float yv;
    bool is_right;
    CurrAnimation cur_anim;
};

struct MiniObjects {
    void GiveDTECS(float* _dt, ECS* _ecs);

    void Draw(int id);
    void Update();
    int GenerateCobweb(float x, float y);


    float* dt;
    ECS*   ecs;

    std::map<int, Obj> objects;
    SDL_Texture* cobweb_texture = LoadImage(global_window_data.rdr, "assets/enemies/cobweb.png");
};