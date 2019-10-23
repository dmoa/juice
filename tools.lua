function AABB(x1, y1, w1, h1, x2, y2, w2, h2)
    return x1 + w1 > x2 and x1 < x2 + w2 
        and y1 + h1 > y2 and y1 < y2 + h2
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

isDown = {
    right = function()
        return (love.keyboard.isDown("right") or love.keyboard.isDown("d") or )
    end
}