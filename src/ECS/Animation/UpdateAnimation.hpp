#pragma once

#include "../EntityInfo.hpp"

#include <SDL2/SDL.h>

bool AnimationTick(ENTITY_NAME e_name, CurrAnimation* anim, float* dt);

void SetAnimation(ENTITY_NAME e_name, CurrAnimation* anim, ANIMATION_TYPE new_type);

void SetAnimationIf(ENTITY_NAME e_name, CurrAnimation* anim, ANIMATION_TYPE new_type);

void UpdateAnimationQuad(ENTITY_NAME e_name, CurrAnimation* anim, int* x, int* y);