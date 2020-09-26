//
// Created by Lado on 25/8/20.
//

#ifndef CRIMSONLAND_MOUSECONTROLLER_H
#define CRIMSONLAND_MOUSECONTROLLER_H

#include "Components.h"
#include "../Game.hpp"

class MouseController: public Component {
public:
    Transform *transform;
    SpriteComponent *sprite;

    void init(void) override;
    void update(void) override;
};


#endif //CRIMSONLAND_MOUSECONTROLLER_H
