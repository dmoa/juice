#include "../EntityInfo.hpp"

std::map<ENTITY_NAME, SOAAnimations> ENTITY_ANIMATION_DATA = {
    {
        PLAYER, {
            {{"idle",0}, {"running",1}, {"attack",2}},
            { 4,      6,                 3          },
            { 0.3,    0.1,               0.13       },
        }
    },
    {
        SPIDER, {
            {{"idle",0}, {"running",1}},
            { 5,      6       },
            { 0.2,    0.1     },
        }
    }
};