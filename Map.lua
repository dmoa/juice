local Map = {
    mapDataCollisions = require("maps/general/mapDataCollision"),
    -- data about when the tiles should go transparent
    mapDataGT = require("maps/general/mapDataGT"),
    -- tiles drawn after the playing is drawn
    afterTiles = {
        withOpacity = {},
        withoutOpacity = {}
    },
    currentMapType = "middle"
}

function Map:draw()
    
    for i, layer in ipairs(self.map.layers) do
        for y = 0, layer.height - 1 do
            for x = 0, layer.width - 1 do
                
                local index = (x + y * layer.width) + 1
                local tid = layer.data[index]
                
                if tid ~= 0 then
                    local quad = self.map.quads[tid]
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
                            self.map.image,
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
            self.map.image,
            block.quad,
            block.x,
            block.y 
        )
    end
    
    love.graphics.setColor(1, 1, 1, 1)
    for k, block in ipairs(self.afterTiles.withoutOpacity) do
        love.graphics.draw(
            self.map.image,
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

    self.map.quads = {}
    local tileset = self.map.tilesets[1]
    self.map.tileset = tileset
    -- hardcoded due to relative path of map file & image file
    self.map.image = love.graphics.newImage("imgs/tileset.png")

    for y = 0, (tileset.imageheight / tileset.tileheight) - 1 do
        for x = 0, (tileset.imagewidth / tileset.tilewidth) - 1 do
            local quad = love.graphics.newQuad(
                x * tileset.tilewidth,
                y * tileset.tileheight,
                tileset.tilewidth,
                tileset.tileheight,
                tileset.imagewidth,
                tileset.imageheight
            )
            table.insert(self.map.quads, quad)
        end
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
                local quad = self.map.quads[tid]
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

    return blocks
end

function Map:moveMap(direction)
    canvas:transition()
    -- black magic ternary statement
    self.currentMapType = (self.currentMapType == "middle") and direction or "middle" 
end

function Map:reloadMap()
    self:generateMap("maps/"..self.currentMapType.."/1")
end

return Map