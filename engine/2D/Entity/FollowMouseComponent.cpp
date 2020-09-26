//
// Created by Lado on 25/8/20.
//

#include "FollowMouseComponent.h"

void FollowMouseComponent::init(void) {
    transform = &entity->getComponent<Transform>();
    sprite = &entity->getComponent<SpriteComponent>();
}

void FollowMouseComponent::update(void) {
    int x;
    int y;
    SDL_GetMouseState(&x, &y);
    transform->position.x = Game::camera.x + x - 32;
    transform->position.y = Game::camera.y + y - 32;
}