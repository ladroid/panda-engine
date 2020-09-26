//
// Created by Lado on 26/8/20.
//

#include "EnemySpawner.h"

extern Manage manage;

EnemySpawnComponent::EnemySpawnComponent(Entity *entityToAttack, std::string id, Vector2D map_size) {
    hero = entityToAttack;
    sprite_id = id;
    countSpawns = 5;
    count = countSpawns;
    mapSize = map_size;
}

void EnemySpawnComponent::init() {
    addSpawns(count);
}

void EnemySpawnComponent::update() {
    Transform *transformHero;
    Transform *transformEnemy;
    if(count == 0) {
        countSpawns += 5;
        count = countSpawns;
        std::cout << count << std::endl;
        addSpawns(count);
        return;
    }
    transformHero = &hero->getComponent<Transform>();
    //auto &spawns(Game::manage.getGroup(group_enemies));
    auto &spawns(manage.getGroup(Game::groupEnemies));
    for(auto &s : spawns) {
        transformEnemy = &s->getComponent<Transform>();
        int delta_x = transformHero->position.x - transformEnemy->position.x;
        int delta_y = transformHero->position.y - transformEnemy->position.y;
        if (delta_x == 0 || delta_y == 0)
            continue ;
        int length = Vector2D::vectorLength(Vector2D(delta_x, delta_y));
        double angle = (atan2(-delta_y, -delta_x) * 180.0) / 3.1416 + 90;
        Vector2D dir = {static_cast<float>((delta_x * 2)/ length), static_cast<float>((delta_y * 2)/ length)};
        transformEnemy->velocity = dir;
        s->getComponent<SpriteComponent>().angle = angle;
    }
}

void EnemySpawnComponent::addSpawns(int n) {
    Transform *transform;
    int delta_x;
    int delta_y;
    int x;
    int y;
    double angle;
    int length;

    transform = &hero->getComponent<Transform>();
    for (int _ = 1; _ <= n; _++)
    {
        int s = rand() % 2;
        x = rand() % Game::camera.w + (Game::camera.x + Game::camera.w) * s;
        y = rand() % Game::camera.h + (Game::camera.y + Game::camera.h) * (1 - s);
        delta_x = x - transform->position.x;
        delta_y = y - transform->position.y;
        angle = (atan2(delta_y, delta_x) * 180.0) / 3.1416 + 90;
        length = Vector2D::vectorLength(Vector2D(delta_x, delta_y));

        auto &enemy(manage.addEntity());
        enemy.addComponents<Transform>(x, y);
        enemy.addComponents<SpriteComponent>("spider");
        enemy.addGroup(Game::groupEnemies);
        std::cout << "ENEMY" << std::endl;
    }
}

void EnemySpawnComponent::killSpawn(Entity *s) {
    s->destroy();
    count--;
}