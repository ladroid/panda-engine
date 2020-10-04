--
-- Created by IntelliJ IDEA.
-- User: lado
-- Date: 28/9/20
-- Time: 2:58 pm
-- To change this template use File | Settings | File Templates.
--

--local FPS = 60
--local frameDelay = math.floor(1000 / FPS)
--
--local frameStart
--local frameTime = 0

local game = Game.new()
game:init("title", "SDL_WINDOWPOS_CENTERED", "SDL_WINDOWPOS_CENTERED", 800, 600, false)
while(game:running()) do
    frameStart = game:get_ticks()

    game:handleEvent()
    game:update()
    game:render()
end
game:clean()
--    frameStart = game:get_ticks() - frameStart
--    if frameDelay > frameTime then
--        sleep(frameDelay - frameTime)
--    end
--end
--game:clean()

