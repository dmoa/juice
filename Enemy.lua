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
            speed = 0.3,
            right = {},
            left = {}
        },
        walking = {
            n_frames = 4,
            speed = 0.3,
            right = {},
            left = {}
        }
    },
    currentImage = nil,
    currentQuad = nil,
    currentAnimation = nil,
    currentDirection = nil,
    currentAnimationIndex = nil,
    animationTick = 0,
    x = 50,
    y = 50,
    drawEnemy = false
}

function Enemy:spawnEnemy(currentLevel)
    self.enemyIndex = currentLevel
    self.currentImage = self.images[self.enemyIndex]

    self.frames.width = self.quadSizes[self.enemyIndex][1]
    self.frames.height = self.quadSizes[self.enemyIndex][2]

    local width = self.frames.width
    local height = self.frames.height

    for i = 1, self.frames.idle.n_frames do
        table.insert(self.frames.idle.right, lg.newQuad((i - 1) * width, 0, 
                                                         width, height, self.currentImage:getDimensions()))
        table.insert(self.frames.idle.left,  lg.newQuad((i - 1 + self.frames.idle.n_frames) * width, 0,
                                                         width, height, self.currentImage:getDimensions()))
    end

    self.currentAnimation = "idle"
    self.currentDirection = "left"
    self.currentAnimationIndex = 1
    self.currentQuad = self.frames[self.currentAnimation][self.currentDirection][self.currentAnimationIndex]

    self.drawEnemy = true
end

function Enemy:draw()   
    if self.drawEnemy then
        lg.draw(self.currentImage, self.currentQuad, math.round(self.x), math.round(self.y))
    end
end

function Enemy:update(dt)
    if self.drawEnemy then
        self.animationTick = self.animationTick - dt
        
        if self.animationTick < 0 then
            self.animationTick = self.frames[self.currentAnimation].speed
            self.currentAnimationIndex = (self.currentAnimationIndex % self.frames[self.currentAnimation].n_frames) + 1
            self.currentQuad = self.frames[self.currentAnimation][self.currentDirection][self.currentAnimationIndex] 
        end
    end
end

return Enemy