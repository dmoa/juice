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

pixelatedShader = lg.newShader([[

    extern vec2 size;
    extern number factor;
    vec4 effect(vec4 color, Image img, vec2 texture_coords, vec2 pixel_coords){
       vec2 tc = floor(texture_coords * size / factor) * factor / size;
       return Texel(img, tc);
    }

]])

crtShader = lg.newShader([[
    extern float elapsed;
    extern float colorI;
    
    vec2 radialDistortion(vec2 coord, float dist) {
        vec2 cc = coord - 0.5;
        dist = dot(cc, cc) * dist + cos(elapsed * .3) * .01;
        return (coord + cc * (1.0 + dist) * dist);
    }
    
    vec4 effect(vec4 color, Image tex, vec2 tc, vec2 pc) {
        vec2 tcr = radialDistortion(tc, .24)  + vec2(.001, 0);
        vec2 tcg = radialDistortion(tc, .20);
        vec2 tcb = radialDistortion(tc, .18) - vec2(.001, 0);
        vec4 res = vec4(Texel(tex, tcr).r, Texel(tex, tcg).g, Texel(tex, tcb).b, 1)
        - cos(tcg.y * 128. * 3.142 * 2) * colorI
        - sin(tcg.x * 128. * 3.142 * 2) * colorI;
        return res * Texel(tex, tcg).a;
    }
]])

function math.round(n)
    return n % 1 >= 0.5 and math.ceil(n) or math.floor(n)
end

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

noiseM = require("libs/noise")