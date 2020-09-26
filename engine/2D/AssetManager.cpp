//
// Created by Lado on 2/7/20.
//

#include "AssetManager.h"
#include "Entity/Components.h"
#include "Entity/Collider.h"
#include "Entity/Projectile.h"

AssetManager::AssetManager(Manage* man) : manager(man)
{}

AssetManager::~AssetManager()
{}

void AssetManager::createProjectile(Vector2D pos, int range, int speed, std::string id) {
    auto& projectile(manager->addEntity());
    projectile.addComponents<Transform>(pos.x, pos.y, 32, 32, 1);
    projectile.addComponents<SpriteComponent>(id, false);
    projectile.addComponents<Projectile>(range, speed);
    projectile.addComponents<Collider>("projectile");
    projectile.addGroup(Game::groupProjectiles);
}

void AssetManager::createProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id) {
    auto& projectile(manager->addEntity());
    projectile.addComponents<Transform>(pos.x, pos.y, 32, 32, 1);
    projectile.addComponents<SpriteComponent>(id, false);
    projectile.addComponents<Projectile>(range, speed, vel);
    projectile.addComponents<Collider>("projectile");
    projectile.addGroup(Game::groupProjectiles);
}

void AssetManager::addTexture(std::string id, const char* path)
{
    textures.emplace(id, Texture::LoadTexture(path));
}

SDL_Texture* AssetManager::getTexture(std::string id)
{
    return textures[id];
}

void AssetManager::addFont(std::string id, std::string path, int sizeFont) {
    fonts.emplace(id, TTF_OpenFont(path.c_str(), sizeFont));
}

TTF_Font * AssetManager::getFont(std::string id) {
    return fonts[id];
}
