local Map = {
    mapData = require("mapData"),
    -- tiles drawn after the playing is drawn
    afterTiles = {}
}

function Map:draw()

    local playerIndex1 = game.player:getBLIndex()
    local playerIndex2 = game.player:getBRIndex()
    
    for i, layer in ipairs(self.map.layers) do
        for y = 0, layer.height - 1 do
            for x = 0, layer.width - 1 do
                
                local index = (x + y * layer.width) + 1
                local tid = layer.data[index]
                
                if tid ~= 0 then
                    local quad = self.map.quads[tid]
                    local xx = x * self.map.tileset.tilewidth
                    local yy = y * self.map.tileset.tileheight
                    
                    if (index == playerIndex1 or index == playerIndex2) and i == 2 and
                         AABB(game.player.x, game.player.y, game.player.quadsData[game.player.size].width, game.player.quadsData[game.player.size].height,
                            xx, yy, self.map.tileset.tilewidth, self.map.tileset.tileheight) then
                                    
                        table.insert(self.afterTiles, {x = xx, y = yy, quad = quad})
                        
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
    love.graphics.print(playerIndex1)
end

function Map:finishDrawing()
    love.graphics.setColor(1, 1, 1, 0.8)

    for k, block in ipairs(self.afterTiles) do
        love.graphics.draw(
            self.map.image,
            block.quad,
            block.x,
            block.y 
        )
    end
    self.afterTiles = {}
    
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
                    x = xx + (self.mapData.xOffsets["_"..tostring(tid)] and self.mapData.xOffsets["_"..tostring(tid)] or 0), 
                    y = yy + (self.mapData.yOffsets["_"..tostring(tid)] and self.mapData.yOffsets["_"..tostring(tid)] or 0),
                    id = tid, 
                    width = self.mapData.widths["_"..tostring(tid)] and self.mapData.widths["_"..tostring(tid)] or self.map.tileset.tilewidth, 
                    height = self.mapData.heights["_"..tostring(tid)] and self.mapData.heights["_"..tostring(tid)] or self.map.tileset.tileheight
                }

                table.insert(blocks, block)
            end
        end
    end

    return blocks
end

return Map