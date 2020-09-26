//
// Created by Lado on 4/6/20.
//

#include "Texture.h"

SDL_Texture *Texture::LoadTexture(const char *fileName) {
    SDL_Surface *tmpSurface = IMG_Load(fileName);
    SDL_Texture *textr = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);

    return textr;
}

void Texture::Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip) {
    SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, NULL, NULL, flip);
}