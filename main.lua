function love.load()
    pixelatedShader = love.graphics.newShader([[
        extern vec2 size;            //vector contains image size, like shader:send('size', {img:getWidth(), img:getHeight()})	
        extern number factor;    //nimber contains sample size, like shader:send('factor', 2), use number is divisible by two
        vec4 effect(vec4 color, Image img, vec2 texture_coords, vec2 pixel_coords){
           vec2 tc = floor(texture_coords * size / factor) * factor / size;
           return Texel(img, tc);
        }
    ]])
    love.graphics.setShader(pixelatedShader)
    windowStartup()
    gameStartup()
end

function love.draw()
    love.graphics.setCanvas(canvas.c)
    love.graphics.clear()

    game:draw()
    
    love.graphics.setCanvas()
    love.graphics.draw(canvas.c, math.floor(canvas.x), math.floor(canvas.y), canvas.r, canvas.scale, canvas.scale, gameWW / 2, gameWH / 2)
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
            canvas.scale = canvas.scale < scale and canvas.scale + dt or canvas.scale
            --canvas.r = canvas.scale < scale and canvas.r + dt or 0
        end
    }
end

function gameStartup()
    game = require("Game")
end