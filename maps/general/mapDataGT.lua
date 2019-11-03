-- go over tiles
-- tiles which have a collision box, 
-- for when they should be drawn in lower opacity

return {
    xOffsets = {
        -- tree
        _35 = 7, _43 = 7, _51 = 7
    },
    yOffsets = {
        -- signposts
        _49 = -3, _50 = -3, _57 = -3, _58 = -3,
    },
    widths = {
        -- tree
        _37 = 9, _45 = 9, _53 = 9
    },
    heights = {
        -- signposts
        _49 = 2, _50 = 2, _57 = 2, _58 = 2,
        -- tree
        _51 = 12, _52 = 14, _53 = 12,
        -- generated blocks
        _89 = 1, _90 = 1, _91 = 1, _93 = 1, _97 = 1, _98 = 1, _99 = 1, _102 = 1, _103 = 1, _104 = 1
    },
    -- exceptions, tiles that should never go transparent
    exceptions = {
        -- left side wall
        _73 = true, _86 = true, _78 = true,
        -- right side walls
        _75 = true, _88 = true, _72 = true,
        -- top wall
        _66 = true,
        -- top right wall
        _67 = true,
        -- top left wall
        _65 = true,
        -- building
        _15 = true, _16 = true, _23 = true, 
        _24 = true, _31 = true, _32 = true,
        -- water
        _12 = true, _13 = true, _14 = true, 
        _20 = true, _21 = true, _22 = true, 
        _28 = true, _29 = true, _30 = true,
        -- tree
        _59 = true, _60 = true, _61 = true
    },
    withoutOpacity = {
        -- signposts
        _49 = true, _50 = true, _57 = true, _58 = true,
        -- generated blocks
        _89 = true, _90 = true, _91 = true, _93 = true, _97 = true, _98 = true, _99 = true, _102 = true, _103 = true, _104 = true
    }
}