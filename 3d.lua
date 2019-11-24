local ss3dScene = {}

local scene = ss3dEngine.newScene(love.graphics.getWidth(), love.graphics.getHeight())
local Timer = 0

scene.camera.pos.x = 0
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
    Pyramids[#Pyramids+1] = ss3dEngine.newModel(pyramidVerts)
    Pyramids[i].wireframe = true
    scene:addModel(Pyramids[i])
end

function ss3dScene:draw()
    scene:render()
end

function ss3dScene:update(dt)
    Timer = Timer + dt/4

    for i=1, #Pyramids do
        Pyramids[i]:setTransform({}, {Timer, cpml.vec3.unit_y, Timer, cpml.vec3.unit_z, Timer, cpml.vec3.unit_x})
    end
end

return ss3dScene