//
// Created by Lado on 6/7/20.
//

#ifndef LOTOS_GRAPHICS2D_H
#define LOTOS_GRAPHICS2D_H

#include "SDL.h"
#include "EntityComponent.h"
#include "../Vector2D.h"
#include <cmath>

class Graphics2D : public Component {
private:
    SDL_Renderer *renderer;
    Vector2D position;
    int radius;
public:
    Graphics2D() {  }
    Graphics2D(SDL_Renderer *renderer, Vector2D pos, int radius) {
        this->renderer = renderer;
        position.x = pos.x;
        position.y = pos.y;
        this->radius = radius;
    }
    void drawCircle(int r, int g, int b, int a) {
       SDL_SetRenderDrawColor(renderer, r, g, b, a);
       for(int x = position.x - radius; x < position.x + radius; x++) {
           for(int y = position.y - radius; y < position.y + radius; y++) {
               if(std::pow(position.y - y, 2) + std::pow(position.x - x, 2) < std::pow(radius, 2)) {
                   SDL_RenderDrawPoint(renderer, x, y);
               }
           }
       }
       SDL_RenderPresent(renderer);
    }
    void drawEllipse(int height, int width, int r, int g, int b, int a) {
        SDL_SetRenderDrawColor(renderer, r, g, b, a);
        for(int x = -height; x < height; x++) {
            for(int y = -width; y < width; y++) {
                if((std::pow(x, 2) * std::pow(height, 2)) + (std::pow(y, 2) * std::pow(width, 2)) < (std::pow(height, 2) * std::pow(width, 2))) {
                    SDL_RenderDrawPoint(renderer, position.x + x, position.y + y);
                }
            }
        }
        SDL_RenderPresent(renderer);
    }
    ~Graphics2D() {

    }
};

#endif //LOTOS_GRAPHICS2D_H
