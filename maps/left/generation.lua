-- 89 is crate
local generation = function(borders, tileLength)

    local grid = {}
    -- Fill each pixel in our grid with simplex noise.
    local function noise()
        for x = 1, 15 do
            for y = 1, 8 do
                grid[x] = grid[x] or {}
                local seed = love.math.random()
                grid[x][y] = noiseM.Simplex2D( x + seed, y + seed) > 0.2 and 1 or 0
            end
        end
    end
    noise()

    local specialIDs = {
        -- numbers represent (in order) down left up right
        -- 1 means connected
        _0000 = 89,
        _1000 = 90,
        _0100 = 91,
        _0010 = 92,
        _0001 = 93,
        _0011 = 94,
        _1010 = 95,
        _0110 = 96,
        _1001 = 97,
        _0101 = 98,
        _1100 = 99,
        _0111 = 100,
        _1011 = 101,
        _1101 = 102,
        _1110 = 103,
        _1111 = 104,
    }

    local function calculateID(x, y)
        -- bottom connected, left connected etc...
        local bottomC = (not (y == #grid[x]) and grid[x][y + 1] == 1) and 1 or 0
        local leftC = (not (x == 1) and grid[x - 1][y] == 1) and 1 or 0
        local upC = (not (y == 1) and grid[x][y - 1] == 1) and 1 or 0
        local rightC = (not (x == #grid) and grid[x + 1][y] == 1) and 1 or 0

        return specialIDs["_"..bottomC..leftC..upC..rightC]
    end

    local blocks = {}
    -- if value is 1 add lava block
    for _x = 1, #grid do
        for _y = 1, #grid[_x] do
            if grid[_x][_y] == 1 then
                
                local _id = calculateID(_x, _y)

                table.insert(blocks, {x = (_x - 1) * tileLength + borders.left, y = (_y - 1) * tileLength + borders.top, 
                                      id = _id})
            end
        end
    end




    return blocks  
end

return generation