//
// Created by Lado on 29/6/20.
//

#ifndef LOTOS_ANIMATION_H
#define LOTOS_ANIMATION_H

struct Animation {
    int index;
    int frame;
    int speed;

    Animation() {}
    Animation(int i, int f, int s) {
        index = i;
        frame = f;
        speed = s;
    }

};

#endif //LOTOS_ANIMATION_H
