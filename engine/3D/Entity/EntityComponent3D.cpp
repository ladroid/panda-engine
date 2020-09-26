//
// Created by Lado on 17/7/20.
//

#include "EntityComponent3D.h"

void Entity::addGroup(Group mGroup) {
    groupBitSet[mGroup] = true;
    manager.addToGroup(this, mGroup);
}