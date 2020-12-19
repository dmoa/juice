#pragma once

#include <map>

#include <SDL_CP.h>
#include "Globals/All.h"
#include "Asset/AssetLoader.h"

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
    SDL_Texture* cobweb_texture = LoadImage(g_window.rdr, "assets/enemies/cobweb.png");
};