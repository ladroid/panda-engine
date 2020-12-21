//
// Created by Lado on 21/6/20.
//

#ifndef LOTOS_COLLIDER_H
#define LOTOS_COLLIDER_H

#include <string>
#include "SDL.h"
#include "Components.h"
#include "Texture.h"
#include "../Game.hpp"

class Collider : public Component {
public:
    SDL_Rect collider;
    std::string tag;
    Transform* transform;

    SDL_Texture *tex;
    SDL_Rect srcR, destR;

    int circleX, circleY;
    int radius;

    Collider(std::string t) {
        tag = t;
    }

    Collider(int circle_x, int circle_y) {
        circleX = circle_x;
        circleY = circle_y;
    }

    Collider(std::string t, int xpos, int ypos, int size) {
        tag = t;
        collider.x = xpos;
        collider.y = ypos;
        collider.h = collider.w = size;
    }

    void init() override {
        if(!entity->hasComponent<Transform>()) {
            entity->addComponents<Transform>();
        }
        transform = &entity->getComponent<Transform>();

        tex = Texture::LoadTexture("C:/Users/UZER/Documents/GameDev/Lotos/Lotos/src/engine/assert/ColTex.png");
        srcR = {0 , 0, 32, 32};
        destR = {collider.x, collider.y, collider.w, collider.h};

        //Game::colliders.push_back(this);
    }

    void update() override {
        if(tag != "terrain") {
            collider.x = static_cast<int>(transform->position.x);
            collider.y = static_cast<int>(transform->position.y);
            collider.h = transform->height * transform->scale;
            collider.w = transform->width * transform->scale;
        }
        destR.x = collider.x - Game::camera.x;
        destR.y = collider.y - Game::camera.y;
    }

    void draw() override {
        Texture::Draw(tex, srcR, destR, SDL_FLIP_NONE);
    }

};

#endif //LOTOS_COLLIDER_H
