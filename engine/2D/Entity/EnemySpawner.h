//
// Created by Lado on 26/8/20.
//

#ifndef CRIMSONLAND_ENEMYSPAWNER_H
#define CRIMSONLAND_ENEMYSPAWNER_H

#include "Components.h"
#include "../Game.hpp"

class EnemySpawnComponent: public Component {
private:
    Entity *hero;
    std::string sprite_id;
    int count;
    int countSpawns;
    Vector2D mapSize;
    //Manage manage;
public:
    EnemySpawnComponent(Entity *entityToAttack, std::string id, Vector2D map_size);
    void init(void) override;
    void update(void) override;
    void addSpawns(int n);
    void killSpawn(Entity *s);
};

#endif //CRIMSONLAND_ENEMYSPAWNER_H
