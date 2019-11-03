local Map = {
    tileset = {
        image = love.graphics.newImage("imgs/tileset.png"),
        quads = {},
        tileLength = 16
    },
    mapDataCollisions = require("maps/general/mapDataCollision"),
    -- data about when the tiles should go transparent
    mapDataGT = require("maps/general/mapDataGT"),
    -- generic borders of any map loaded
    borders = {
        top = 16,
        left = 5,
        right = 5,
        bottom = 5
    },
    -- tiles drawn after the playing is drawn
    afterTiles = {
        withOpacity = {},
        withoutOpacity = {}
    },
    currentMapType = "middle"
}

for y = 0, (Map.tileset.image:getHeight() / Map.tileset.tileLength) - 1 do
    for x = 0, (Map.tileset.image:getWidth() / Map.tileset.tileLength) - 1 do
        local quad = love.graphics.newQuad(
            x * Map.tileset.tileLength,
            y * Map.tileset.tileLength,
            Map.tileset.tileLength,
            Map.tileset.tileLength,
            Map.tileset.image:getDimensions()
        )
        table.insert(Map.tileset.quads, quad)
    end
end

function Map:draw()
    
    for i, layer in ipairs(self.map.layers) do

        -- draw generated blocks right after ground
        if i == 2 then
            for _, block in ipairs(self.map.generatedTiles) do
                if i > 1 and not (self.mapDataGT.exceptions["_"..tostring(block.id)]) and
                AABB(game.player.x, 
                     game.player.y, 
                     game.player.quadsData[game.player.size].width, 
                     game.player.quadsData[game.player.size].height,
                     block.x + (self.mapDataGT.xOffsets["_"..tostring(block.id)] and self.mapDataGT.xOffsets["_"..tostring(block.id)] or 0),
                     block.y + (self.mapDataGT.yOffsets["_"..tostring(block.id)] and self.mapDataGT.yOffsets["_"..tostring(block.id)] or 0), 
                     (self.mapDataGT.widths["_"..tostring(block.id)] and self.mapDataGT.widths["_"..tostring(block.id)] or self.map.tileset.tilewidth),
                     (self.mapDataGT.heights["_"..tostring(block.id)] and self.mapDataGT.heights["_"..tostring(block.id)] or self.map.tileset.tileheight)) 
                     then
                 
                 table.insert(self.mapDataGT.withoutOpacity["_"..tostring(block.id)] and self.afterTiles.withoutOpacity 
                              or self.afterTiles.withOpacity, 
                              {x = block.x, y = block.y, quad = self.tileset.quads[block.id]})

                            print("OOF")
                 
                else
                 love.graphics.draw(
                    self.tileset.image,
                    self.tileset.quads[block.id],
                    block.x,
                    block.y
                 )
                end
            end
        end

        for y = 0, layer.height - 1 do
            for x = 0, layer.width - 1 do
                
                local index = (x + y * layer.width) + 1
                local tid = layer.data[index]
                
                if tid ~= 0 then
                    local quad = self.tileset.quads[tid]
                    local xx = x * self.map.tileset.tilewidth
                    local yy = y * self.map.tileset.tileheight
                    
                    if i > 1 and not (self.mapDataGT.exceptions["_"..tostring(tid)]) and
                       AABB(game.player.x, 
                            game.player.y, 
                            game.player.quadsData[game.player.size].width, 
                            game.player.quadsData[game.player.size].height,
                            xx + (self.mapDataGT.xOffsets["_"..tostring(tid)] and self.mapDataGT.xOffsets["_"..tostring(tid)] or 0),
                            yy + (self.mapDataGT.yOffsets["_"..tostring(tid)] and self.mapDataGT.yOffsets["_"..tostring(tid)] or 0), 
                            (self.mapDataGT.widths["_"..tostring(tid)] and self.mapDataGT.widths["_"..tostring(tid)] or self.map.tileset.tilewidth),
                            (self.mapDataGT.heights["_"..tostring(tid)] and self.mapDataGT.heights["_"..tostring(tid)] or self.map.tileset.tileheight)) then
                        
                        table.insert(self.mapDataGT.withoutOpacity["_"..tostring(tid)] and self.afterTiles.withoutOpacity 
                                     or self.afterTiles.withOpacity, 
                                     {x = xx, y = yy, quad = quad})
                        
                    else
                        love.graphics.draw(
                            self.tileset.image,
                            quad,
                            xx,
                            yy
                        )
                    end
                    
                end
            end
        end
        
    end

    --love.graphics.rectangle("fill", game.player.x, game.player.y, game.player.quadsData[game.player.size].width, game.player.quadsData[game.player.size].height)
end

function Map:finishDrawing()

    love.graphics.setColor(1, 1, 1, 0.8)
    for k, block in ipairs(self.afterTiles.withOpacity) do
        love.graphics.draw(
            self.tileset.image,
            block.quad,
            block.x,
            block.y 
        )
    end
    
    love.graphics.setColor(1, 1, 1, 1)
    for k, block in ipairs(self.afterTiles.withoutOpacity) do
        love.graphics.draw(
            self.tileset.image,
            block.quad,
            block.x,
            block.y 
        )
    end

    self.afterTiles = {
        withOpacity = {},
        withoutOpacity = {}
    }
    
    love.graphics.setColor(1, 1, 1, 1)
end

function Map:update(dt)
end

function Map:generateMap(path)

    self.map = require(path)
    local tileset = self.map.tilesets[1]
    self.map.tileset = tileset

    -- randomising grass tiles
    for i, layer in ipairs(self.map.layers) do
        for y = 0, layer.height - 1 do
            for x = 0, layer.width - 1 do
                
                local index = (x + y * layer.width) + 1
                local tid = layer.data[index]
                
                if tid ~= 0 then

                    if tid < 6 then
                        layer.data[index] = love.math.random(5)
                    end
                    
                end
            end
        end
    end

    self.map.generatedTiles = {}
    if not (self.currentMapType == "middle") then
        local generate = require("maps/"..self.currentMapType.."/generation")
        self.map.generatedTiles = generate(self.borders, self.tileset.tileLength)
    end

end

function Map:getTiles(layerIndex)
    
    local blocks = {}

    layer = self.map.layers[layerIndex]
    for y = 0, layer.height - 1 do
        for x = 0, layer.width - 1 do
            local index = (x + y * layer.width) + 1
            local tid = layer.data[index]

            if tid ~= 0 then
                local quad = self.tileset.quads[tid]
                local xx = x * self.map.tileset.tilewidth
                local yy = y * self.map.tileset.tileheight
                
                local block = {
                    x = xx + (self.mapDataCollisions.xOffsets["_"..tostring(tid)] and self.mapDataCollisions.xOffsets["_"..tostring(tid)] or 0), 
                    y = yy + (self.mapDataCollisions.yOffsets["_"..tostring(tid)] and self.mapDataCollisions.yOffsets["_"..tostring(tid)] or 0),
                    id = tid, 
                    width = self.mapDataCollisions.widths["_"..tostring(tid)] and self.mapDataCollisions.widths["_"..tostring(tid)] or self.map.tileset.tilewidth, 
                    height = self.mapDataCollisions.heights["_"..tostring(tid)] and self.mapDataCollisions.heights["_"..tostring(tid)] or self.map.tileset.tileheight
                }

                table.insert(blocks, block)
            end
        end
    end

    for _, _block in ipairs(self.map.generatedTiles) do
        local block = {
            x = _block.x + (self.mapDataCollisions.xOffsets["_"..tostring(_block.id)] and self.mapDataCollisions.xOffsets["_"..tostring(_block.id)] or 0), 
            y = _block.y + (self.mapDataCollisions.yOffsets["_"..tostring(_block.id)] and self.mapDataCollisions.yOffsets["_"..tostring(_block.id)] or 0),
            id = _block.id, 
            width = self.mapDataCollisions.widths["_"..tostring(_block.id)] and self.mapDataCollisions.widths["_"..tostring(_block.id)] or self.map.tileset.tilewidth, 
            height = self.mapDataCollisions.heights["_"..tostring(_block.id)] and self.mapDataCollisions.heights["_"..tostring(_block.id)] or self.map.tileset.tileheight
        }

        table.insert(blocks, block)
    end

    return blocks
end

function Map:moveMap(direction)
    canvas:startTransition()
    -- black magic ternary statement
    self.currentMapType = (self.currentMapType == "middle") and direction or "middle"
end

function Map:reloadMap()
    self:generateMap("maps/"..self.currentMapType.."/1")
end

return Map