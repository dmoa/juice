function AABB(x1, y1, w1, h1, x2, y2, w2, h2)
    return x1 + w1 > x2 and x1 < x2 + w2 
        and y1 + h1 > y2 and y1 < y2 + h2
end

function AABBTouching(x1, y1, w1, h1, x2, y2, w2, h2)
    return x1 + w1 >= x2 and x1 <= x2 + w2 
        and y1 + h1 >= y2 and y1 <= y2 + h2
end

function AABBHorizontal(x1, w1, x2, w2)
    return x1 + w1 > x2 and x1 < x2 + w2 
end

function AABBVertical(y1, h1, y2, h2)
    return y1 + h1 > y2 and y1 < y2 + h2 
end

pixelatedShader = love.graphics.newShader([[

    extern vec2 size;
    extern number factor;
    vec4 effect(vec4 color, Image img, vec2 texture_coords, vec2 pixel_coords){
       vec2 tc = floor(texture_coords * size / factor) * factor / size;
       return Texel(img, tc);
    }

]])

joystick = love.joystick.getJoysticks()[1]
-- joystick:setVibration(1, 1, 0.5)

keyIsDown = {
    right = function()
        return (love.keyboard.isDown("right") or love.keyboard.isDown("d") or (joystick and joystick:getAxis(1) > 0.5))
    end,
    left = function()
        return (love.keyboard.isDown("left") or love.keyboard.isDown("a") or (joystick and joystick:getAxis(1) < -0.5))
    end,
    up = function()
        return (love.keyboard.isDown("up") or love.keyboard.isDown("w") or (joystick and joystick:getAxis(2) < -0.5))
    end,
    down = function()
        return (love.keyboard.isDown("down") or love.keyboard.isDown("s") or (joystick and joystick:getAxis(2) > 0.5))
    end
}