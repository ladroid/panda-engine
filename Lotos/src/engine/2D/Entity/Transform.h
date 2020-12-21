//
// Created by Lado on 11/6/20.
//

#ifndef LOTOS_TRANSFORMCOMPONENT_H
#define LOTOS_TRANSFORMCOMPONENT_H

//
// Created by Lado on 11/6/20.
//

#ifndef LOTOS_POSITIONCOMPONET_H
#define LOTOS_POSITIONCOMPONET_H

#include "Components.h"
#include "../Vector2D.h"
#include <iostream>

class Transform : public Component {
public:
    Vector2D position;
    Vector2D velocity;

    int height = 32;
    int width = 32;
    int scale = 1;

    int speed = 3;

    Transform() {
        position.Zero();
    }

    Transform(int s) {
//        position.Zero();
        position.x = 400;
        position.y = 320;
        scale = s;
    }

    Transform(float x, float y) {
        position.Zero();
    }

    Transform(float x, float y, int h, int w, int s) {
        position.x = x;
        position.y = y;
        height = h;
        width = w;
        scale = s;
    }

    void x(float x) {
        position.x = x;
    }

    float x() {
        return position.x;
    }

    void y(float y) {
        position.y = y;
    }

    float y() {
        return position.y;
    }

    void init() override {
        velocity.Zero();
    }

    void update() override {
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
    }

    void setPos(float x, float y) {
        position.x = x;
        position.y = y;
    }
};

#endif //LOTOS_POSITIONCOMPONET_H


#endif //LOTOS_TRANSFORMCOMPONENT_H
