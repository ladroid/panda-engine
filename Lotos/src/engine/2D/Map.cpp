//
// Created by Lado on 5/6/20.
//

#include "Map.h"
#include "Texture.h"
#include "Entity/EntityComponent.h"
#include "Entity/TileComponent.h"
#include "Entity/Components.h"
#include "Entity/Collider.h"
#include "Game.hpp"

extern Manage manage;

Map::Map(std::string tID, int ms, int ts) : texID(tID), mapScale(ms), tileSize(ts) {
    scaledSize = ms * ts;
}

void Map::LoadMap(std::string path, int sizeX, int sizeY) {
    char tile;
    std::fstream mapFile;
    mapFile.open(path);

    int srcX, srcY;

    for(int y = 0; y < sizeY; y++) {
        for(int x = 0; x < sizeX; x++) {
            mapFile.get(tile);
            srcY = atoi(&tile) * tileSize;
            mapFile.get(tile);
            srcX = atoi(&tile) * tileSize;
            addTile(srcX, srcY, x * scaledSize, y * scaledSize);
            mapFile.ignore();
        }
    }

    mapFile.ignore();

    for(int y = 0; y < sizeY; y++) {
        for(int x = 0; x < sizeX; x++) {
            mapFile.get(tile);
            if(tile == '1') {
                auto &tcol(manage.addEntity());
                tcol.addComponents<Collider>("terrain", x * scaledSize, y * scaledSize, scaledSize);
                tcol.addGroup(Game::groupColliders);
            }
            mapFile.ignore();
        }
    }

    mapFile.close();
}

void Map::addTile(int srcX, int srcY, int xpos, int ypos) {
    auto& tile(manage.addEntity());
    tile.addComponents<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, texID);
    tile.addGroup(Game::groupMap);
}

Map::~Map() {

}