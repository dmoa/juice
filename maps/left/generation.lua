-- 89 is crate
local generation = function(borders)
    local block = {
        x = love.math.random(borders.left, gameWW - borders.right - game.map.tileset.tileLength), 
        y = love.math.random(borders.top, gameWH - borders.bottom - game.map.tileset.tileLength), 
        id = 89
    }

    
    local path = {
        {
            4, 0, 0, 0
        }, 
        {
            0, 0, 1, 1
        },
        {
            0, 0, 2, 0
        }
    }

    sectionWidth = 50
    sectionHeight = 50

    -- path ids,
    -- 1: only open bottom
    -- 2: only open top
    -- 3: only open left
    -- 4: only open right
    -- 5: only open bottom and top
    -- 6: only open bottom and left
    -- 7: only open bottom and right
    -- 8: only open top and left
    -- 9: only open top and right
    -- 10: only open left and right

    local moves = {"left", "up", "down"}

    local newSection = function(_currentSection)
        while true do
            local move = moves[love.math.random(#moves)]
            if move == "left" then
                return {x = _currentSection.x - 1, y = _currentSection.y}, move
            end
            if move == "up" then
                if (_currentSection.y - 1) >= 1 and path[_currentSection.y - 1][_currentSection.x] == 0 then
                    return {x = _currentSection.x, y = _currentSection.y - 1}, move
                end
            end
            if move == "down" then
                if (_currentSection.y + 1) <= #path and path[_currentSection.y + 1][_currentSection.x] == 0 then
                    return {x = _currentSection.x, y = _currentSection.y + 1}, move
                end
            end
        end
    end

    local currentSection = {x = 4, y = 2}

    -- while the algorithm has not reached the outside of the map
    -- while not (currentSection.x == 0) do
    --     path[currentSection.y][currentSection.x] = 1
    --     currentSection, move = newSection(currentSection)
    -- end

    -- printing out shape of math
    for k, v in ipairs(path) do
        for k2, v2 in ipairs(v) do
            print(v2)
        end
        print("--")
    end

    local blocks = {}

    local makeTopCover = function(xIndex, yIndex)
        for i = 0, 2 do
            table.insert(blocks, {x = (xIndex - 1) * sectionWidth + (16 * i), y = (yIndex - 1) * sectionHeight, id = 89})
        end
    end
    local makeBottomCover = function(xIndex, yIndex)
        for i = 0, 2 do
            table.insert(blocks, {x = (xIndex - 1) * sectionWidth + (16 * i), y = (yIndex - 1) * sectionHeight + 100, id = 89})
        end
    end
    local makeLeftCover = function(xIndex, yIndex)
        for i = 0, 2 do
            table.insert(blocks, {x = (xIndex - 1) * sectionWidth, y = (yIndex - 1) * sectionHeight + (16 * i), id = 89})
        end
    end
    local makeRightCover = function(xIndex, yIndex)
        for i = 0, 2 do
            table.insert(blocks, {x = (xIndex - 1) * sectionWidth + 100, y = (yIndex - 1) * sectionHeight + (16 * i), id = 89})
        end
    end

    for yIndex, row in ipairs(path) do
        for xIndex, value in ipairs(row) do
            if value == 1 then
                makeTopCover(xIndex, yIndex)
                makeLeftCover(xIndex, yIndex)
                makeRightCover(xIndex, yIndex)
            elseif value == 2 then
                makeBottomCover(xIndex, yIndex)
                makeLeftCover(xIndex, yIndex)
                makeRightCover(xIndex, yIndex)
            elseif value == 3 then
                makeTopCover(xIndex, yIndex)
                makeBottomCover(xIndex, yIndex)
                makeRightCover(xIndex, yIndex)
            elseif value == 4 then
                makeTopCover(xIndex, yIndex)
                makeBottomCover(xIndex, yIndex)
                makeLeftCover(xIndex, yIndex)
            elseif value == 5 then
                makeLeftCover(xIndex, yIndex)
                makeRightCover(xIndex, yIndex)
            elseif value == 6 then
                makeTopCover(xIndex, yIndex)
                makeRightCover(xIndex, yIndex)
            elseif value == 7 then
                makeTopCover(xIndex, yIndex)
                makeLeftCover(xIndex, yIndex)
            elseif value == 8 then
                makeBottomCover(xIndex, yIndex)
                makeRightCover(xIndex, yIndex)
            elseif value == 9 then
                makeBottomCover(xIndex, yIndex)
                makeLeftCover(xIndex, yIndex)
            elseif value == 10 then
                makeTopCover(xIndex, yIndex)
                makeBottomCover(xIndex, yIndex)
            end
        end
    end


    return blocks  
end

return generation