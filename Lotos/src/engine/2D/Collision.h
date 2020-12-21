//
// Created by Lado on 21/6/20.
//

#ifndef LOTOS_COLLISION_H
#define LOTOS_COLLISION_H

#include <iostream>
#include <cmath>
#include "SDL.h"
#include "Entity/Collider.h"

class Collider;

struct Circle {
    int x, y;
    int radius;
};

class Collision {
public:
    static bool AABB(const SDL_Rect& rectA, const SDL_Rect& rectB);
    static bool AABB(const Collider& colA, const Collider& colB);
    static bool AABBCircle(const Circle &cA, const Circle &cB);
    static bool AABBCircle(const Collider& colA, const Collider& colB);
};

#endif //LOTOS_COLLISION_H
