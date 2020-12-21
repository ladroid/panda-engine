#ifndef Game_hpp
#define Game_hpp

#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>
#include <vector>
#include "AssetManager.h"

class Collider;
class AssetManager;

class Game {
private:
//    bool isRunning;
    SDL_Window *window;
    //SDL_Renderer *renderer;
    int cnt = 0;
public:
    enum groupLabels : std::size_t {groupMap, groupPlayers, groupEnemies, groupColliders, groupProjectiles};
    static bool isRunning;
    static SDL_Event event;
    static SDL_Renderer* renderer;
    static SDL_Rect camera;
    static AssetManager* assets;

    Game();
    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();
    bool running() { return isRunning; }
    ~Game();
};

#endif