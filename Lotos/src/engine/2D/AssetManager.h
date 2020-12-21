//
// Created by Lado on 2/7/20.
//

#ifndef LOTOS_ASSETMANAGER_H
#define LOTOS_ASSETMANAGER_H

#include <map>
#include <string>
#include "SDL.h"
#include "SDL_ttf.h"
#include "Texture.h"
#include "Vector2D.h"
#include "Entity/EntityComponent.h"

class AssetManager
{
private:
    Manage* manager;
    std::map<std::string, SDL_Texture*> textures;
    std::map<std::string, TTF_Font*> fonts;
public:
    AssetManager(Manage* man);

    //gameobjects
    void createProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id);
    void createProjectile(Vector2D pos, int range, int speed, std::string id);

    //texture management
    void addTexture(std::string id, const char* path);
    SDL_Texture* getTexture(std::string id);

    //fonts
    void addFont(std::string id, std::string path, int sizeFont);
    TTF_Font* getFont(std::string id);

    ~AssetManager();
};

#endif //LOTOS_ASSETMANAGER_H
