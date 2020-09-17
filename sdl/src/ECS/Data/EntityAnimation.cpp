#pragma once

#include "../EntityInfo.hpp"

const std::map<ENTITY_TYPE, SOAAnimations> ENTITY_ANIMATION_DATA = {
    {
    PLAYER_TYPE,
        {
            16, 16,
            {{"idle",0}, {"running",1}},
            { 4,      6       },
            { 0.3,    0.1     },
            { 0,      4       }
        },
    }
};