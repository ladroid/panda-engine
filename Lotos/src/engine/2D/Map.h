//
// Created by Lado on 5/6/20.
//

#ifndef LOTOS_MAP_H
#define LOTOS_MAP_H

#include <string>
#include <fstream>
#include "Game.hpp"

class Map {
private:
    std::string texID;
    int mapScale;
    int tileSize;
    int scaledSize;
public:
    Map(std::string tID, int ms, int ts);
    void LoadMap(std::string path, int sizeX, int sizeY);
    void addTile(int srcX, int srcY, int xpos, int ypos);
    ~Map();
};

#endif //LOTOS_MAP_H
