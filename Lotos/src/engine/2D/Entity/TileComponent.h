//
// Created by Lado on 27/6/20.
//

#ifndef LOTOS_TILECOMPONENT_H
#define LOTOS_TILECOMPONENT_H

#include "Components.h"
#include "SDL.h"
#include <string>

class TileComponent: public Component {
public:
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;
    Vector2D position;

    TileComponent() {

    };

    TileComponent(int srcX, int srcY, int xpos, int ypos, int tsize, int tscale, std::string id) {
        texture= Game::assets->getTexture(id);
        position.x = xpos;
        position.y = ypos;
        srcRect.x = srcX;
        srcRect.y = srcY;
        srcRect.w = srcRect.h = tsize;
        destRect.x = xpos;
        destRect.y = ypos;
        destRect.w = destRect.h = tsize * tscale;
    }

    void update() override {
        destRect.x = position.x - Game::camera.x;
        destRect.y = position.y - Game::camera.y;
    }

    void draw() override {
        Texture::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
    }

    ~TileComponent() {
        SDL_DestroyTexture(texture);
    }
};

#endif //LOTOS_TILECOMPONENT_H
