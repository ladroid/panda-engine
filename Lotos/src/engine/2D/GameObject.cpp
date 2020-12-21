//
// Created by Lado on 4/6/20.
//

#include "GameObject.h"
#include "Texture.h"

GameObject::GameObject(const char *textureSheet, int x, int y) {
    objTexture = Texture::LoadTexture(textureSheet);
    xpos = x;
    ypos = y;
}

void GameObject::update() {
    xpos++;
    ypos++;

    //scale
    srcRect.h = 16;
    srcRect.w = 16;

    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xpos;
    destRect.y = ypos;

    destRect.w = srcRect.w * 2;
    destRect.h = srcRect.h * 2;
}

void GameObject::render() {
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}