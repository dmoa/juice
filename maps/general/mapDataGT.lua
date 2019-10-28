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
        -- right side wall
        _75 = true,
        -- top wall
        _66 = true,
        -- building
        _15 = true,
        _16 = true,
        _23 = true,
        _24 = true,
        _31 = true,
        _32 = true,
        _12 = true,
        _13 = true,
        _14 = true,
        _20 = true,
        _21 = true,
        _22 = true,
        _28 = true,
        _29 = true,
        _30 = true
    }
}