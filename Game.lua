local Game = {
    map = require("Map"),
    player = require("Player"),
}

Game.map:generateMap("maps/middle/1")

function Game:draw()
    self.map:draw()
    self.player:draw()
    self.map:finishDrawing()
end

function Game:update(dt)
    self.map:update(dt)
    self.player:update(dt)
end

return Game