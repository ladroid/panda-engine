//
// Created by Lado on 28/6/20.
//

#include "EntityComponent.h"

void Entity::addGroup(Group mGroup) {
    groupBitSet[mGroup] = true;
    manager.addToGroup(this, mGroup);
}