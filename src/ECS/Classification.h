#pragma once

enum ENTITY_TYPE {
    PLAYER_TYPE,
    MAP_TYPE,
    ENEMY_TYPE,
    MINIOBJECT_TYPE
};

enum ENTITY_NAME {
    PLAYER,

    TREE1,
    TREE2,
    LOG,
    STONE,

    SPIDER,

    COBWEB
};

enum ANIMATION_TYPE {
    ANIM_NONE,
    IDLE,
    RUN,
    ATTACK,
    STUN,
    TO_STUN,
    EXPAND
};