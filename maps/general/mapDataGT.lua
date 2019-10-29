-- go over tiles
-- tiles which have a collision box, 
-- for when they should be drawn in lower opacity

return {
    xOffsets = {

    },
    yOffsets = {

    },
    widths = {

    },
    heights = {

    },
    -- exceptions, tiles that should never go transparent
    exceptions = {
        -- left side wall
        _73 = true,
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
}