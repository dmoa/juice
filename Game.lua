local Game = {
    map = require("Map"),
    player = require("Player"),
    overlay = require("Overlay")
}

Game.map:generateMap("maps/middle/1")

function Game:draw()
    self.map:draw()
    self.player:draw()
    self.map:finishDrawing()
    self.overlay:draw()
end

function Game:update(dt)
    self.map:update(dt)
    self.player:update(dt)
end

function Game:reloadLevel()
    self.map:reloadMap()
    self.player:reloadPosition()
end

return Game