local ss3dScene = {}

local scene = ss3dEngine.newScene(lg.getWidth(), lg.getHeight())
local Timer = 0

local canvas = lg.newCanvas()

scene.camera.pos.x = 0
scene.camera.pos.y = 8
scene.camera.pos.z = 8

scene.ambientLight = 1
scene.ambientVector = {0, -3, 0}

-- local pyramidVerts = {}
-- pyramidVerts[#pyramidVerts+1] = {-1,-1,-1}
-- pyramidVerts[#pyramidVerts+1] = {-1,1,1}
-- pyramidVerts[#pyramidVerts+1] = {1,1,-1}

-- pyramidVerts[#pyramidVerts+1] = {-1,1,1}
-- pyramidVerts[#pyramidVerts+1] = {1,1,-1}
-- pyramidVerts[#pyramidVerts+1] = {1,-1,1}

-- pyramidVerts[#pyramidVerts+1] = {-1,-1,-1}
-- pyramidVerts[#pyramidVerts+1] = {1,1,-1}
-- pyramidVerts[#pyramidVerts+1] = {1,-1,1}

-- pyramidVerts[#pyramidVerts+1] = {-1,-1,-1}
-- pyramidVerts[#pyramidVerts+1] = {-1,1,1}
-- pyramidVerts[#pyramidVerts+1] = {1,-1,1}

-- Pyramids = {}
-- for i=1, 4 do
--     Pyramids[#Pyramids+1] = ss3dEngine.newModel(pyramidVerts, lg.newImage("imgs/3Dtexture.png"))
--     Pyramids[i].wireframe = true
--     scene:addModel(Pyramids[i])
-- end

-- local square = ss3dEngine.newModel(ss 3dEngine.loadObj("3dObjects/square.obj"), lg.newImage("imgs/texture3.png"))
-- scene:addModel(square)

function ss3dScene:draw()
    local engineCanvas, x, y, width, height, rotation, scaleX, scaleY, offsetX, offsetY = scene:getRender()

    lg.setCanvas(canvas)
    lg.clear()
    lg.setShader(pixelatedShader)

    lg.draw(engineCanvas, x, y, width, height, rotation, scaleX, scaleY, offsetX, offsetY)
    
    lg.setCanvas()

    if shaderOn then lg.setShader(crtShader) end
    lg.draw(canvas)
    
    lg.setShader()
end

function ss3dScene:update(dt)
    Timer = Timer + dt * 7

    -- for i=1, #Pyramids do
    --     Pyramids[i]:setTransform({}, {Timer, cpml.vec3.unit_y, Timer, cpml.vec3.unit_z, Timer, cpml.vec3.unit_x})
    -- end
    --square:setTransform({0, 3, 0}, {Timer, cpml.vec3.unit_y, 0, cpml.vec3.unit_z, 0, cpml.vec3.unit_x})
end

return ss3dScene