//
// Created by Lado on 25/8/20.
//

#include "MouseController.h"
#include <iostream>

extern Manage manage;

void MouseController::init(void) {
    transform = &entity->getComponent<Transform>();
    sprite = &entity->getComponent<SpriteComponent>();
}

void MouseController::update(void) {
    static int bulletDelay = 0;
    int delta_x;
    int delta_y;
    int x;
    int y;
    SDL_GetMouseState(&x, &y);

    delta_x = transform->position.x - Game::camera.x - x;
    delta_y = transform->position.y - Game::camera.y - y;
    sprite->angle = (atan2(delta_y, delta_x) * 180.0) / 3.1416 + 90;

    if (Game::event.type == SDL_MOUSEBUTTONDOWN)
    {
        std::cout << "AAA1" << std::endl;
        if (Game::event.button.button == SDL_BUTTON_LEFT && bulletDelay == 0)
        {
            std::cout << "AAA2" << std::endl;
            int length = Vector2D::vectorLength(Vector2D(delta_x, delta_y));
            Vector2D dir = {static_cast<float>(- delta_x * 5/ length), static_cast<float>(- delta_y * 5/ length)};
            auto &bullet(manage.addEntity());
            bullet.addComponents<Transform>(transform->position.x, transform->position.y, 32, 32, 1, 2, dir);
            bullet.addComponents<SpriteComponent>("fire");
            bullet.addGroup(Game::groupBullets);
            bulletDelay = 10;
        }
    }
    if (Game::event.type == SDL_MOUSEBUTTONUP) {
        std::cout << "BBB1" << std::endl;
        if (Game::event.button.button == SDL_BUTTON_LEFT) {
            std::cout << "BBB1" << std::endl;
            bulletDelay = 0;
        }
    }

    if (bulletDelay != 0) {
        bulletDelay--;
    }
}