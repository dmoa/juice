function love.load()
    windowStartup()
    gameStartup()

    require("tools")
end

function love.draw()
    love.graphics.setCanvas(canvas.c)
    love.graphics.setShader()
    love.graphics.clear()
    
    
    game:draw()
    
    love.graphics.setCanvas()
    love.graphics.setShader(pixelatedShader)
    love.graphics.draw(canvas.c, canvas.x, canvas.y, canvas.r, canvas.scale, canvas.scale, gameWW / 2, gameWH / 2)

    love.graphics.print(love.timer.getFPS())
    love.graphics.print(canvas.scale, 0, 15)
end

function love.update(dt)
    game:update(dt)
    canvas:update(dt)
    pixelatedShader:send("size", {gameWW, gameWH})
    -- I honestly have no idea why or how it works when I added 0.0001, but it does, so...
    pixelatedShader:send("factor", scale / (canvas.scale))
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
        shrink = false
    }
    function canvas:update(dt)
        if self.shrink then
            self.scale = self.scale + dt * -10
            if self.scale < 0 then
                self.shrink = false
                game:reloadLevel()
            end
        else
            self.scale = self.scale < scale and self.scale + dt * 4 or scale
        end
    end
    function canvas:transition(dt)
        self.shrink = true
    end

end

function gameStartup()
    game = require("Game")
end