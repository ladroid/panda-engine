//
// Created by Lado on 4/6/20.
//

#ifndef LOTOS_TEXTURE_H
#define LOTOS_TEXTURE_H

#include "Game.hpp"

class Texture {
public:
    static SDL_Texture *LoadTexture(const char* fileName);
    static void Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip);
};

#endif //LOTOS_TEXTURE_H
