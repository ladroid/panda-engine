//
// Created by Lado on 12/6/20.
//

#ifndef LOTOS_INPUTHANDLER_H
#define LOTOS_INPUTHANDLER_H

#include "../Game.hpp"
#include "Components.h"


class InputHandler : public Component {
public:
    Transform *transform;
    SpriteComponent *sprite;

    void init() override {
        transform = &entity->getComponent<Transform>();
        sprite = &entity->getComponent<SpriteComponent>();
    }

    void update() override {
        if(Game::event.type == SDL_KEYDOWN) {
            switch (Game::event.key.keysym.sym) {
                case SDLK_w:
                    transform->velocity.y = -1;
                    sprite->play("Walk");
                    break;
                case SDLK_a:
                    transform->velocity.x = -1;
                    sprite->play("Walk");
                    sprite->flip = SDL_FLIP_HORIZONTAL;
                    break;
                case SDLK_d:
                    transform->velocity.x = 1;
                    sprite->play("Walk");
                    break;
                case SDLK_s:
                    transform->velocity.y = 1;
                    sprite->play("Walk");
                    break;
                default:
                    break;
            }
        }
        if(Game::event.type == SDL_KEYUP) {
            switch (Game::event.key.keysym.sym) {
                case SDLK_w:
                    transform->velocity.y = 0;
                    sprite->play("Idle");
                    break;
                case SDLK_a:
                    transform->velocity.x = 0;
                    sprite->play("Idle");
                    sprite->flip = SDL_FLIP_NONE;
                    break;
                case SDLK_d:
                    transform->velocity.x = 0;
                    sprite->play("Idle");
                    break;
                case SDLK_s:
                    transform->velocity.y = 0;
                    sprite->play("Idle");
                    break;
                default:
                    break;
            }
        }
    }
};

#endif //LOTOS_INPUTHANDLER_H
