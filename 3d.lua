local ss3dScene = {}

local scene = ss3dEngine.newScene(love.graphics.getWidth(), love.graphics.getHeight())
local Timer = 0

scene.camera.pos.x = 5
scene.camera.pos.z = 5

local pyramidVerts = {}
pyramidVerts[#pyramidVerts+1] = {-1,-1,-1}
pyramidVerts[#pyramidVerts+1] = {-1,1,1}
pyramidVerts[#pyramidVerts+1] = {1,1,-1}

pyramidVerts[#pyramidVerts+1] = {-1,1,1}
pyramidVerts[#pyramidVerts+1] = {1,1,-1}
pyramidVerts[#pyramidVerts+1] = {1,-1,1}

pyramidVerts[#pyramidVerts+1] = {-1,-1,-1}
pyramidVerts[#pyramidVerts+1] = {1,1,-1}
pyramidVerts[#pyramidVerts+1] = {1,-1,1}

pyramidVerts[#pyramidVerts+1] = {-1,-1,-1}
pyramidVerts[#pyramidVerts+1] = {-1,1,1}
pyramidVerts[#pyramidVerts+1] = {1,-1,1}

Pyramids = {}
for i=1, 4 do
    Pyramids[#Pyramids+1] = ss3dEngine.newModel(pyramidVerts, love.graphics.newImage("imgs/3Dtexture.png"))
    Pyramids[i].wireframe = true
    scene:addModel(Pyramids[i])
end

AlakazamModel = ss3dEngine.newModel(ss3dEngine.loadObj("alakazam.obj"), love.graphics.newImage("imgs/3Dtexture.png"))
--scene:addModel(AlakazamModel)

function ss3dScene:draw()
    local canvas, x, y, width, height, rotation, scaleX, scaleY, offsetX, offsetY = scene:getRender()
    if shaderOn then lg.setShader(crtShader) end
    lg.draw(canvas, x, y, width, height, rotation, scaleX, scaleY, offsetX, offsetY)
end

function ss3dScene:update(dt)
    Timer = Timer + dt/4

    for i=1, #Pyramids do
        Pyramids[i]:setTransform({}, {Timer, cpml.vec3.unit_y, Timer, cpml.vec3.unit_z, Timer, cpml.vec3.unit_x})
    end
end

return ss3dScene