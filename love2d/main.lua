function love.load()
    lg = love.graphics
    lk = love.keyboard
    lm = love.math
    lj = love.joystick

    require("tools")
    
    windowStartup()
    gameStartup()
    ss3dEngineStartup()

    --lg.setBackgroundColor(0.52,0.57,0.69)

    scene3d = require("3d")
end

function love.draw()
    -- lg.push("all")
    -- lg.translate(gameWW/2, gameWH/2)
    -- lg.scale(canvas.scale)
    -- lg.translawate(-gameWW/2, -gameWH/2)
    
    lg.setCanvas(canvas.c)
    lg.setShader()
    lg.clear()
    
    game:draw()
    
    lg.setCanvas()
    if shaderOn then lg.setShader(crtShader) end
    lg.draw(canvas.c, 0, 0, 0, scale)
    scene3d:draw()
    
    lg.print(love.timer.getFPS())
    lg.print(canvas.scale, 0, 15)
    lg.print(game.map.currentMapType, 0, 30)
end

function love.update(dt)
    game:update(dt )
    canvas:update(dt)
    
    pixelatedShader:send("size", {gameWW, gameWH})
    pixelatedShader:send("factor", 1)
    crtShader:send("colorI", 0.03 / canvas.scale)
    
    scene3d:update(dt)
    
end

function love.keypressed(key)
    if key == "escape" then love.event.quit() end
    if key == "p" then shaderOn = not shaderOn end
end

function love.joystickpressed(_, button)
    if joystick:isGamepadDown('b') then
        love.event.quit()
    end
end

function windowStartup()
    love.mouse.setVisible(false)
    lg.setDefaultFilter("nearest", "nearest", 1, 1)
    WW, WH = lg.getDimensions()
    gameWW = 256
    gameWH = 144
    
    
    canvas = {
        c = lg.newCanvas(gameWW, gameWH),
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
    
    scale = lg.getWidth() / canvas.c:getWidth()

    shaderOn = true
end

function gameStartup()
    game = require("Game")
end

function ss3dEngineStartup()
end