#include "Entity.h"


std::unordered_map<ENTITY_NAME, std::unordered_map<ANIMATION_TYPE, AnimationInfo> > ANIMATION_DATA = {
    {
        PLAYER, {
            {IDLE,   {4, 0.3,  0}},
            {RUN,    {6, 0.1,  1}},
            {ATTACK, {3, 0.13, 2}}
        }
    },
    {
        SPIDER, {
            {IDLE,   {5, 0.2,  0}},
            {RUN,    {6, 0.1,  1}},
            {ATTACK, {4, 0.25, 2}},
        }
    }
};