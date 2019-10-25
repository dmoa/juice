function love.load()
    windowStartup()
    gameStartup()

    require("tools")
end

function love.draw()
    love.graphics.setCanvas(canvas.c)
    love.graphics.clear()
    love.graphics.setShader()
    
    
    game:draw()
    
    love.graphics.setCanvas()
    love.graphics.setShader(pixelatedShader)
    love.graphics.draw(canvas.c, canvas.x, canvas.y, canvas.r, canvas.scale, canvas.scale, gameWW / 2, gameWH / 2)

    love.graphics.print(love.timer.getFPS())
end

function love.update(dt)
    game:update(dt)
    canvas:update(dt)
    pixelatedShader:send("size", {gameWW, gameWH})
    pixelatedShader:send("factor", scale / canvas.scale)
end

function love.keypressed(key)
    if key == "escape" then love.event.quit() end
end
function love.joystickpressed(_, button)
    if joystick:isGamepadDown('b') then
        love.event.quit()
    end
end

function windowStartup()
    love.mouse.setVisible(false)
    love.graphics.setDefaultFilter("nearest", "nearest", 1, 1)
    WW, WH = love.graphics.getDimensions()
    gameWW = 256
    gameWH = 144
    scale = WH / gameWH

    canvas = {
        c = love.graphics.newCanvas(gameWW, gameWH),
        x = WW / 2,
        y = WH / 2,
        r = 0,
        scale = 0,
    }
    function canvas:update(dt)
        self.scale = self.scale < scale and self.scale + dt * 5 or self.scale
    end

end

function gameStartup()
    game = require("Game")
end