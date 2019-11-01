-- 89 is explodable crate
local generation = function(borders)
    local block = {
        x = love.math.random(borders.left, gameWW - borders.right - game.map.tileset.tileLength), 
        y = love.math.random(borders.top, gameWH - borders.bottom - game.map.tileset.tileLength), 
        id = 89
    }
    return {block}
end

return generation