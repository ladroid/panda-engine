//
// Created by Lado on 2/6/20.
//
#include "2D/Game.hpp"
#include "SDL.h"

Game *game = nullptr;

const int FPS = 60;
const int frameDelay = 1000 / FPS;
Uint32 frameStart;
int frameTime;

int main(int argc, char *argv[]) {

    game = new Game();
    game->init("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
    while(game->running()) {
        frameStart = SDL_GetTicks(); //milliseconds when initialize game

        game->handleEvents();
        game->update();
        game->render();

        frameStart = SDL_GetTicks() - frameStart; //milliseconds -> how long takes handling the event & updating the object in rendering
        if(frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    game->clean();
    return 0;
}