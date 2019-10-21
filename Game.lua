local Game = {
    map = require("Map")
}

Game.map:generateMap("maps/map")

function Game:draw()
    self.map:draw()
end

function Game:update(dt)
    self.map:update(dt)
end

return Game