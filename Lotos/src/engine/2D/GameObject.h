//
// Created by Lado on 4/6/20.
//

#ifndef LOTOS_GAMEOBJECT_H
#define LOTOS_GAMEOBJECT_H

#include "Game.hpp"

class GameObject {
private:
    int xpos, ypos;
    SDL_Texture *objTexture;
    SDL_Rect srcRect, destRect;
public:
    GameObject(const char *textureSheet, int x, int y);
    void update();
    void render();
    ~GameObject();
};

#endif //LOTOS_GAMEOBJECT_H
