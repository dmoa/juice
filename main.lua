function love.load()
    windowStartup()
    gameStartup()
end

function love.draw()
    
end

function love.update(dt)
end

function love.keypressed(key)
    if key == "escape" then love.event.quit() end
end

function windowStartup()
    love.mouse.setVisible(false)
    WW, WH = love.graphics.getDimensions()
    gameWW = 160
    gameWH = 90
    scale = WH / gameWH
    canvas = {
        c = love.graphics.newCanvas(gameWW, gameWH),
        x = 0,
        y = 0
    }
end

function gameStartup()
    player = require("Player")
end