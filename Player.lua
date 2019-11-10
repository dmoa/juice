local Player = {
    size = 1, -- 3 mushrooms sizes
    x = 50,
    y = 50,
    v = 50,
    directionV = math.pow(50 * 50 / 2, 0.5),
    oldX = nil,
    oldY = nil,
    image = love.graphics.newImage("imgs/player.png"),
    quadsData = {
        {
            offsetX = 0,
            offsetY = 0,
            width = 16,
            height = 16,
            frames = {
                idleRight = {
                    quads = {},
                    n_frames = 4,
                    frame_speed = 0.3
                },
                walkingRight = {
                    quads = {},
                    n_frames = 4,
                    frame_speed = 0.1
                },
                idleLeft = {
                    quads = {},
                    n_frames = 4,
                    frame_speed = 0.3
                },
                walkingLeft = {
                    quads = {},
                    n_frames = 4,
                    frame_speed = 0.1
                },
            },
            frameTypes = {"idleRight", "walkingRight", "idleLeft", "walkingLeft"}
        }
    },
    currentAnimation = "idleRight",
    animationIndex = 1,
    frameRate = 0.10,
    frameTimer = 0,
    currentQuad = nil,
    direction = "right",
    walking = false,
    collisionData = {
        {
            width = 12,
            height = 2,
            offsetX = 2,
            offsetY = 14
        }
    },
    startingMapPos = {
        x = 0,
        y = 0
    }
}

local frameCounter = 0
 
for k, frameT in ipairs(Player.quadsData[1].frameTypes) do
    
    if k > 1 then   
        frameCounter = frameCounter + Player.quadsData[1].frames[Player.quadsData[1].frameTypes[k - 1]].n_frames
    end

    for i = 1, Player.quadsData[1].frames[frameT].n_frames do

        local actualIndex = i + frameCounter

        table.insert(Player.quadsData[1].frames[frameT].quads,
            love.graphics.newQuad(
                (actualIndex - 1) * Player.quadsData[1].width,
                0,
                Player.quadsData[1].width,
                Player.quadsData[1].height,
                Player.image:getDimensions() 
            )
        )
    end
end

Player.currentQuad = Player.quadsData[1].frames.idleRight.quads[1]


function Player:draw()
    love.graphics.draw(self.image, self.currentQuad, math.round(self.x), self.y)
    --love.graphics.rectangle("line", self.x, self.y, 16, 16)
end

function Player:update(dt)
    self:animationTick(dt)
    self:controlsUpdate(dt)
    self:collisionUpdate(dt)
    self:mapUpdate()
end

function Player:animationTick(dt)
    self.currentQuad = self.quadsData[self.size].frames[self.currentAnimation].quads[self.animationIndex]
    self.frameTimer = self.frameTimer - dt
    if self.frameTimer < 0 then
        self.frameTimer = self.quadsData[self.size].frames[self.currentAnimation].frame_speed
        self.animationIndex = (self.animationIndex % self.quadsData[self.size].frames[self.currentAnimation].n_frames) + 1
    end
end

function Player:controlsUpdate(dt)

    self.oldX = self.x 
    self.oldY = self.y 
        
    -- do not react if pressing opposite buttons
    if not (keyIsDown.right() and keyIsDown.left()) and not (keyIsDown.up() and keyIsDown.down()) then
        -- there must be a better way to do this
        if keyIsDown.right() then 

            if (not self.walking) or (not (self.direction == "right")) then
                self:changeAnimation("walkingRight")
                self.direction = "right"
                self.walking = true
            end

        end
        if keyIsDown.left() then 

            if (not self.walking) or (not (self.direction == "left")) then 
                self:changeAnimation("walkingLeft")
                self.direction = "left"
                self.walking = true
            end

        end
        if keyIsDown.down() then

            if not self.walking then
                self.walking = true
                if self.direction == "left" then
                    self:changeAnimation("walkingLeft")
                else
                    self:changeAnimation("walkingRight")
                end            
            end
        
        end
        if keyIsDown.up() then
            
            if not self.walking then
                self.walking = true
                if self.direction == "left" then
                    self:changeAnimation("walkingLeft")
                else
                    self:changeAnimation("walkingRight")
                end            
            end

        end

        -- complicated, because you have to make sure going diagonally is the same speed as any other direction
        if keyIsDown.down() then
            if keyIsDown.right() then
                self.x = self.x + self.directionV * dt
                self.y = self.y + self.directionV * dt
            elseif keyIsDown.left() then
                self.x = self.x - self.directionV * dt
                self.y = self.y + self.directionV * dt
            else
                self.y = self.y + self.v * dt
            end
        elseif keyIsDown.up() then
            if keyIsDown.right() then
                self.x = self.x + self.directionV * dt
                self.y = self.y - self.directionV * dt
            elseif keyIsDown.left() then
                self.x = self.x - self.directionV * dt
                self.y = self.y - self.directionV * dt
            else
                self.y = self.y - self.v * dt
            end
        elseif keyIsDown.right() then
            self.x = self.x + self.v * dt
        elseif keyIsDown.left() then
            self.x = self.x - self.v * dt
        end

    end

    if (not keyIsDown.right()) and (not keyIsDown.left())
        and (not keyIsDown.down()) and (not keyIsDown.up()) 
        or (keyIsDown.right() and keyIsDown.left()) or 
        (keyIsDown.up() and keyIsDown.down()) then
        if self.walking then
            if self.direction == "right" then
                self:changeAnimation("idleRight")
            else
                self:changeAnimation("idleLeft")
            end
        end
        self.walking = false
    end
end

function Player:changeAnimation(newAnimation)
    self.currentAnimation = newAnimation
    self.frameTimer = 0 
    self.animationIndex = 1
end

function Player:collisionUpdate()

    local px = self.x + self.collisionData[self.size].offsetX
    local py = self.y + self.collisionData[self.size].offsetY
    local oldpx = self.oldX + self.collisionData[self.size].offsetX
    local oldpy = self.oldY + self.collisionData[self.size].offsetY
    local pw = self.collisionData[self.size].width
    local ph = self.collisionData[self.size].height


    for k, tile in ipairs(game.map:getTiles(3)) do
        if AABB(px, py, pw, ph, tile.x, tile.y, tile.width, tile.height) then

            if AABBVertical(oldpy, ph, tile.y, tile.height) then
                if px + pw / 2 < tile.x + pw / 2 then
                    local pushback = px + pw - tile.x
                    px = px - pushback
                else
                    local pushback = tile.x + tile.width - px
                    px = px + pushback
                end
            elseif AABBHorizontal(oldpx, pw, tile.x, tile.width) then
                if py + ph / 2 < tile.y + ph / 2 then
                    local pushback = py + ph - tile.y
                    py = py - pushback
                else
                    local pushback = tile.y + tile.height - py
                    py = py + pushback
                end
            end
            
        end
    end

    self.x = px - self.collisionData[self.size].offsetX
    self.y = py - self.collisionData[self.size].offsetY

end

-- changes map if out of bounds
function Player:mapUpdate()
    if canvas.scale == 1 then
        if self.x + self.quadsData[self.size].width < 0 then
            game.map:moveMap("left")
            -- y position doesn't change
            self.startingMapPos.y = self.y
            self.startingMapPos.x = gameWW - self.quadsData[self.size].width - 10
        end
        if self.x > gameWW then
            game.map:moveMap("right")
            self.startingMapPos.y = self.y
            self.startingMapPos.x = 20
        end
        if self.y + self.quadsData[self.size].height < 0 then
            game.map:moveMap("up")
        end
        if self.y > gameWH then
            game.map:moveMap("down")
        end
    end
end

function Player:reloadPosition()
    self.x = self.startingMapPos.x
    self.y = self.startingMapPos.y
end

function Player:getBRIndex()
    local indexX = math.floor((self.x + self.collisionData[self.size].width + self.collisionData[self.size].offsetX) / game.map.map.tileset.tilewidth) + 1
    local indexY = math.floor((self.y + self.collisionData[self.size].height + self.collisionData[self.size].offsetY) / game.map.map.tileset.tileheight)
    return indexY * (gameWW / game.map.map.tileset.tilewidth) + indexX
end

function Player:getBLIndex()
    local indexX = math.floor((self.x + self.collisionData[self.size].offsetX) / game.map.map.tileset.tilewidth) + 1
    local indexY = math.floor((self.y + self.collisionData[self.size].height + self.collisionData[self.size].offsetY) / game.map.map.tileset.tileheight)
    return indexY * (gameWW / game.map.map.tileset.tilewidth) + indexX
end

return Player