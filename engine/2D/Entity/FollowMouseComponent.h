//
// Created by Lado on 25/8/20.
//

#ifndef CRIMSONLAND_FOLLOWMOUSECOMPONENT_H
#define CRIMSONLAND_FOLLOWMOUSECOMPONENT_H

#include "Components.h"

class FollowMouseComponent: public Component {
public:
    Transform *transform;
    SpriteComponent *sprite;

    void init(void) override;
    void update(void) override;
};


#endif //CRIMSONLAND_FOLLOWMOUSECOMPONENT_H
