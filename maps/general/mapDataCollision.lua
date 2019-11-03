return {
    
    -- offset / width / height only mentioned if required, i.e. tile doesn't fit
    -- proportions
    xOffsets = {
        -- signposts
        _49 = 5, _50 = 5, _57 = 5, _58 = 5,
        -- right side wall
        _75 = 11, _88 = 11, _72 = 11,
        -- bottom + right side wall
        _83 = 11,
        -- top + right side wall
        _67 = 5,
        -- building
        _15 = 3, _23 = 3, _31 = 3
    },
    yOffsets = {
        -- signposts
        _49 = 10, _50 = 10, _57 = 10, _58 = 10,
        -- bottom wall
        _82 = 11, _70 = 11, _68 = 11,
        -- building
        _15 = 4, _16 = 4,
        -- generated blocks
        _91 = 4, _92 = 4
    },
    widths = {
        -- signposts
        _49 = 5, _50 = 5, _57 = 5, _58 = 5,
        -- left side wall
        _73 = 5, _86 = 5, _78 = 5,
        -- right side walls
        _75 = 5, _88 = 5, _72 = 5,
        -- bottom + left side wall
        _81 = 5,
        -- bottom + right side wall
        _83 = 11,
        -- top + left side wall
        _65 = 5,
        -- top + right side wall
        _67 = 5,
        -- building 
        _15 = 13, _23 = 13, _31 = 13,
        _16 = 13, _24 = 13, _32 = 13,
    },
    heights = {
        -- signposts
        _49 = 4, _50 = 4, _57 = 4, _58 = 4,
        -- bottom wall
        _82 = 5, _70 = 11, _68 = 11,
        -- building
        _15 = 12, _16 = 12,
        _31 = 12, _32 = 12,
        -- generated blocks
        _91 = 12, _92 = 12
    }
}