-- 89 is crate
local generation = function(borders, tileLength)

    local grid = {}
    -- Fill each pixel in our grid with simplex noise.
    local function noise()
        for x = 1, 15 do
            for y = 1, 8 do
                grid[x] = grid[x] or {}
                grid[x][y] = noiseM.Simplex2D( x + love.math.random(), y + love.math.random()) > 0.3 and 1 or 0
            end
        end
    end
    noise()

    local blocks = {}
    -- if value is 1 add lava block
    for _x = 1, #grid do
        for _y = 1, #grid[_x] do
            if grid[_x][_y] == 1 then
                local _id = (not (y == #grid[_x]) and grid[_x][_y + 1] == 1) and 92 or 91
                table.insert(blocks, {x = (_x - 1) * tileLength + borders.left, y = (_y - 1) * tileLength + borders.top, id = _id})
            end
        end
    end


    return blocks  
end

return generation