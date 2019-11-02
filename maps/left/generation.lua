-- 89 is crate
local generation = function(borders)
    local block = {
        x = love.math.random(borders.left, gameWW - borders.right - game.map.tileset.tileLength), 
        y = love.math.random(borders.top, gameWH - borders.bottom - game.map.tileset.tileLength), 
        id = 89,
    }

    local blocks = {}


    return blocks  
end

return generation