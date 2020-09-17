#pragma once

#include "../EntityInfo.hpp"

#include <SDL2/SDL.h>

void AnimationTick(float* dt, std::string* curr_anim, float* tick, int* curr_frame, ENTITY_NAME name);

void SetAnimation(std::string* curr_anim, std::string new_anim, float* tick, int* curr_frame, ENTITY_NAME name);

void UpdateAnimationQuad(std::string curr_anim, int curr_frame, ENTITY_NAME name, int* x, int* y);