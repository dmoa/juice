-- 89 is crate
local generation = function(borders, tileLength)

    local grid = {}
    -- Fill each pixel in our grid with simplex noise.
    local function noise()
        for x = 1, 32 do
            for y = 1, 18 do
                grid[x] = grid[x] or {}
                local seed = love.math.random()
                grid[x][y] = noiseM.Simplex2D( x + seed * 0.17, y + seed * 0.17) > 0.2 and 1 or 0
            end
        end
    end
    noise()

    -- local specialIDs = {
    --     -- numbers represent (in order) down left up right
    --     -- 1 means connected
    --     _0000 = 89,
    --     _1000 = 90,
    --     _0100 = 91,
    --     _0010 = 92,
    --     _0001 = 93,
    --     _0011 = 94,
    --     _1010 = 95,
    --     _0110 = 96,
    --     _1001 = 97,
    --     _0101 = 98,
    --     _1100 = 99,
    --     _0111 = 100,
    --     _1011 = 101,
    --     _1101 = 102,
    --     _1110 = 103,
    --     _1111 = 104,
    -- }

    local function calculateID(xIndex, yIndex)
    --     -- bottom connected, left connected etc...
    --     local bottomC = (not (y == #grid[x]) and grid[x][y + 1] == 1) and 1 or 0
    --     local leftC = (not (x == 1) and grid[x - 1][y] == 1) and 1 or 0
    --     local upC = (not (y == 1) and grid[x][y - 1] == 1) and 1 or 0
    --     local rightC = (not (x == #grid) and grid[x + 1][y] == 1) and 1 or 0
        local extras = {}
        if (xIndex ~= 1) and (grid[xIndex - 1][yIndex] == 0) then
            table.insert(extras, 100)
        end
        if (xIndex ~= #grid) and (grid[xIndex + 1][yIndex] == 0) then
            table.insert(extras, 102)
        end
        if (yIndex ~= 1) and (grid[xIndex][yIndex - 1] == 0) then
            table.insert(extras, 101)
        end
        if (yIndex ~= #grid[xIndex]) and (grid[xIndex][yIndex + 1] == 0) then
            table.insert(extras, 99)
        end    

        -- if not (xIndex == #grid[xIndex]) and (grid[xIndex][yIndex + 1] == 0) then
        --     table.insert(extras, 91)
        -- end

        return extras
    end

    local blocks = {
        blocks = {},
        addons = {}
    }
    -- if value is 1 add lava block
    for xIndex = 1, #grid - 1 do
        for yIndex = 1, #grid[xIndex] - 1 do
            if grid[xIndex][yIndex] == 1 then
                if (xIndex == 1) or (yIndex == 1) or (xIndex < #grid - 1 and 
                   (grid[xIndex - 1][yIndex - 1] ~= 1 and grid[xIndex + 1][yIndex - 1] ~= 1)) then

                    local _id = (grid[xIndex][yIndex - 1] == 1) and 98 or 97
                    
                    table.insert(blocks.blocks, {x = (xIndex - 1) * tileLength + borders.left, y = (yIndex - 1) * tileLength + borders.top - 1, 
                    id = _id})
                    
                else
                    grid[xIndex][yIndex] = 0
                end
            end
        end
    end

    for xIndex = 1, #grid - 1 do
        for yIndex = 1, #grid[xIndex] - 1 do
            if grid[xIndex][yIndex] == 1 then
                local cornerTiles = calculateID(xIndex, yIndex)

                for _, id in ipairs(cornerTiles) do
                    table.insert(blocks.addons, {x = (xIndex - 1) * tileLength + borders.left, y = (yIndex - 1) * tileLength + borders.top - 1, 
                    id = id})
                end
            end
        end
    end


    return blocks  

end

return generation