function love.load()
    windowStartup()
    gameStartup()

    require("tools")
end

function love.draw()
    -- love.graphics.push("all")
    -- love.graphics.translate(gameWW/2, gameWH/2)
    -- love.graphics.scale(canvas.scale)
    -- love.graphics.translate(-gameWW/2, -gameWH/2)
    
    love.graphics.setCanvas(canvas.c)
    love.graphics.setShader()
    love.graphics.clear()
    
    game:draw()
    
    love.graphics.setCanvas()
    love.graphics.setShader(crtShader)
    love.graphics.draw(canvas.c, 0, 0, 0, scale)

    love.graphics.print(love.timer.getFPS())
    love.graphics.print(canvas.scale, 0, 15)
    love.graphics.print(game.map.currentMapType, 0, 30)
end

function love.update(dt)
    game:update(dt)
    canvas:update(dt)
    -- pixelatedShader:send("size", {gameWW, gameWH})
    -- pixelatedShader:send("factor", 1 / canvas.scale)
    crtShader:send("colorI", 0.03 / canvas.scale)
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
    gameWW = 512
    gameWH = 288
    
    
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
            if self.scale < 0.1 then
                self.shrink = false
                game:reloadLevel()
            end
        else
            self.scale = math.min(1, self.scale + dt)
        end
    end
    function canvas:startTransition(dt)
        self.shrink = true
    end

    canvas.c:setWrap("clampzero")
    
    scale = love.graphics.getWidth() / canvas.c:getWidth()
end

function gameStartup()
    game = require("Game")
end