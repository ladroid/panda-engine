//
// Created by Lado on 21/6/20.
//

#include "Collision.h"


bool Collision::AABB(const SDL_Rect &rectA, const SDL_Rect &rectB) {
    if(rectA.x + rectA.w >= rectB.x && rectB.x + rectB.w >= rectA.x &&
       rectA.y + rectA.h >= rectB.y && rectB.y + rectB.h >= rectA.y) {
        return true;
    }
    return false;
}

bool Collision::AABB(const Collider &colA, const Collider &colB) {
    if (AABB(colA.collider, colB.collider)) {
        std::cout << colA.tag << " hit: " << colB.tag << std::endl;
        return true;
    } else {
        return false;
    }
}

bool Collision::AABBCircle(const Circle &cA, const Circle &cB) {
    int distance = sqrt(pow(cB.x - cA.x, 2) + pow(cB.y - cA.y, 2));
    if(pow(cA.radius + cB.radius, 2) > distance) {
        return true;
    } else {
        return false;
    }
}

bool Collision::AABBCircle(const Collider &colA, const Collider &colB) {
    int distance = sqrt(pow(colB.circleX - colA.circleX, 2) + pow(colB.circleY - colA.circleY, 2));
    if(pow(colB.radius + colA.radius, 2) > distance) {
        return true;
    } else {
        return false;
    }
}