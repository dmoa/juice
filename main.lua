function love.load()
    lg = love.graphics
    lk = love.keyboard
    lm = love.math
    lj = love.joystick

    require("tools")
    
    windowStartup()
    gameStartup()
    ss3dEngineStartup()
end

function love.draw()
    -- lg.push("all")
    -- lg.translate(gameWW/2, gameWH/2)
    -- lg.scale(canvas.scale)
    -- lg.translawate(-gameWW/2, -gameWH/2)
    
    -- lg.setCanvas(canvas.c)
    -- lg.setShader()
    -- lg.clear()
    
    -- game:draw()
    
    -- lg.setCanvas()
    -- if shaderOn then lg.setShader(crtShader) end
    -- lg.draw(canvas.c, 0, 0, 0, scale)

    -- lg.print(love.timer.getFPS())
    -- lg.print(canvas.scale, 0, 15)
    -- lg.print(game.map.currentMapType, 0, 30)
    love.graphics.setColor(1,1,1)
    ss3dScene:render()
end

function love.update(dt)
    game:update(dt )
    canvas:update(dt)
    -- pixelatedShader:send("size", {gameWW, gameWH})
    -- pixelatedShader:send("factor", 1 / canvas.scale)
    crtShader:send("colorI", 0.03 / canvas.scale)
    Timer = dt / 4
    TetrahedronModel:setTransform({math.cos(Timer + math.pi*0.5)*12, math.sin(Timer)*0.75 +1, math.sin(Timer *math.pi*0.5)*12}, {Timer, cpml.vec3.unit_y, Timer, cpml.vec3.unit_z, Timer, cpml.vec3.unit_x})
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
    gameWW = 512
    gameWH = 288
    
    
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

    shaderOn = false
end

function gameStartup()
    game = require("Game")
end

function ss3dEngineStartup()
    ss3dScene = ss3dEngine.newScene(love.graphics.getWidth(), love.graphics.getHeight())
    ss3dScene.camera.pos.x = 0
    ss3dScene.camera.pos.z = 5

    local tetrahedron = {
        {-1,-1,-1},
        {-1,1,1},
        {1,1,-1},
    
        {-1,1,1},
        {1,1,-1},
        {1,-1,1},
    
        {-1,-1,-1},
        {1,1,-1},
        {1,-1,1},
    
        {-1,-1,-1},
        {-1,1,1},
        {1,-1,1},
    }
    TetrahedronModel = ss3dEngine.newModel(tetrahedron, lg.newImage("imgs/3Dtexture.png"))
    ss3dScene:addModel(TetrahedronModel)
end