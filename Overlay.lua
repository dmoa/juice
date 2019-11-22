local Overlay = {
    items = {},
    tilesetImage = love.graphics.newImage("imgs/overlay.png"),
    tilesetL = 16,
    quads = {}
}

for i = 0, Overlay.tilesetImage:getWidth() / Overlay.tilesetL - 1 do
    table.insert(Overlay.quads, 
                 love.graphics.newQuad(i * Overlay.tilesetL, i * Overlay.tilesetL, 
                                       Overlay.tilesetL, Overlay.tilesetL, 
                                       Overlay.tilesetImage:getDimensions()))
end

function Overlay:draw()
    love.graphics.setColor(0, 0, 0)
    love.graphics.rectangle("line", 0, gameWH - game.map.tileset.tileLength,
                             gameWW, game.map.tileset.tileLength)
    love.graphics.setColor(0.5, 1, 1)
    love.graphics.rectangle("fill", 0, gameWH - game.map.tileset.tileLength,
                             gameWW, game.map.tileset.tileLength)
    love.graphics.setColor(1, 1, 1)
end

return Overlay