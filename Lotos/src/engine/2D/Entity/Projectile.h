//
// Created by Lado on 2/7/20.
//

#ifndef LOTOS_PROJECTILE_H
#define LOTOS_PROJECTILE_H

#include "EntityComponent.h"
#include "..\2D\Vector2D.h"
#include "Transform.h"

class Projectile : public Component {
private:
    Transform* transform;
    int range = 0;
    int speed = 0;
    int distance = 0;
    Vector2D velocity;
public:
    Projectile(int rng, int sp) : range(rng), speed(sp) {  }
    Projectile(int rng, int sp, Vector2D vel) : range(rng), speed(sp), velocity(vel) {  }

    void init() override {
        transform = &entity->getComponent<Transform>();
        transform->velocity = velocity;
    }

    void update() override {
        distance += speed;

        if (distance > range) {
            std::cout << "Out of Range" << std::endl;
            entity->destroy();
        }
        else if (transform->position.x > Game::camera.x + Game::camera.w ||
                 transform->position.x < Game::camera.x ||
                 transform->position.y > Game::camera.y + Game::camera.h ||
                 transform->position.y < Game::camera.y) {
            std::cout << "Out of bounds!" << std::endl;
            entity->destroy();
        }
    }
    ~Projectile() {

    }
};

#endif //LOTOS_PROJECTILE_H
