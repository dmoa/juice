function love.load()
    windowStartup()
    gameStartup()
    pixelatedShader = love.graphics.newShader([[

        extern vec2 size;
        extern number factor;
        vec4 effect(vec4 color, Image img, vec2 texture_coords, vec2 pixel_coords){
           vec2 tc = floor(texture_coords * size / factor) * factor / size;
           return Texel(img, tc);
        }
    
    ]])
end

function love.draw()
    love.graphics.setCanvas(canvas.c)
    love.graphics.clear()
    
    pixelatedShader:send("size", {WW, WH})
    pixelatedShader:send("factor", scale / canvas.scale)
    love.graphics.setShader(pixelatedShader)
    
    game:draw()
    
    love.graphics.setCanvas()
    
    love.graphics.setShader()

    love.graphics.draw(canvas.c, canvas.x, canvas.y, 0, canvas.scale, canvas.scale, gameWW / 2, gameWH / 2)
end

function love.update(dt)
    game:update(dt)
    canvas.update(dt)
end

function love.keypressed(key)
    if key == "escape" then love.event.quit() end
end

function windowStartup()
    love.mouse.setVisible(false)
    love.graphics.setDefaultFilter("nearest", "nearest", 1, 1)
    WW, WH = love.graphics.getDimensions()
    gameWW = 512
    gameWH = 288
    scale = WH / gameWH
    canvas = {
        c = love.graphics.newCanvas(gameWW, gameWH),
        x = WW / 2,
        y = WH / 2,
        r = 0,
        scale = 0,
        update = function(dt)
            canvas.scale = canvas.scale < scale and canvas.scale + dt * 3 or canvas.scale
            --canvas.r = canvas.scale < scale and canvas.r + dt or 0
        end
    }
end

function gameStartup()
    game = require("Game")
end