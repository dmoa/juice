local Enemy = {
    images = {
        lg.newImage("imgs/enemies/small.png"),
        lg.newImage("imgs/enemies/medium.png"),
        lg.newImage("imgs/enemies/big.png")
    },
    quadSizes = {
        {16, 16},
        {16, 21},
        {32, 32}
    },
    frames = {
        width = nil,
        height = nil,
        idle = {
            n_frames = 4,
            speed = 0.3
            right = {},
            left = {}
        },
        walking = {
            n_frames = 4,
            speed = 0.3,
            right = {},
            left = {}
        }
    }
    currentImage = nil,
}

function Enemy:spawnEnemy(currentLevel)
    self.enemyIndex = currentLevel
    self.currentImage = self.images[self.enemyIndex]

    self.frames.width = self.quadSizes[self.enemyIndex]
    self.frames.height = self.quadSizes[self.enemyIndex]

    local width = self.frames.width
    local height = self.frames.height

    for i = 1, self.frames.idle.n_frames do
        table.insert(self.frames.idle.right, lg.newQuad((i - 1) * width, 0, 
                                                         width, height, self.currentImage:getDimensions()))
        table.insert(self.frames.idle.left,  lg.newQuad((i - 1 + self.frames.n_frames) * width, 0,
                                                         width, height, self.currentImage:getDimensions()))
    end
end

function Enemy:draw()
end

function Enemy:update(dt)
end

return Enemy