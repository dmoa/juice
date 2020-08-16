local Overlay = {
    items = {},
    tilesetImage = lg.newImage("imgs/overlay.png"),
    tilesetL = 16,
    quads = {}
}

for i = 0, Overlay.tilesetImage:getWidth() / Overlay.tilesetL - 1 do
    table.insert(Overlay.quads, 
                 lg.newQuad(i * Overlay.tilesetL, i * Overlay.tilesetL, 
                            Overlay.tilesetL, Overlay.tilesetL, 
                            Overlay.tilesetImage:getDimensions()))
end

function Overlay:draw()
    lg.setColor(0, 0, 0)
    lg.rectangle("line", 0, gameWH - game.map.tileset.tileLength,
                            gameWW, game.map.tileset.tileLength)
    lg.setColor(0.5, 1, 1)
    lg.rectangle("fill", 0, gameWH - game.map.tileset.tileLength,
                            gameWW, game.map.tileset.tileLength)
    lg.setColor(1, 1, 1)

    lg.setColor(0, 0, 0)
    --lg.print("by Stan O | stan.xyz", gameWW - game.map.tileset.tileLength * 8, 
      --                               gameWH - game.map.tileset.tileLength)

    lg.setColor(1, 1, 1)
    for i = 1, game.player.hp do 
        lg.draw(self.tilesetImage, self.quads[1], (i - 1) * 18, gameWH - game.map.tileset.tileLength)
    end
end

return Overlay