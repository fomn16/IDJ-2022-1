#ifndef __TILESET_H__
#define __TILESET_H__

#include <string>

#include "Sprite.hpp"
#include "GameObject.hpp"

class TileSet{
    public:
        TileSet(GameObject& associated, int tileWidth, int tileHeight, std::string file);
        void RenderTile(unsigned int index, float x, float y);
        int GetTileWidth();
        int GetTileHeight();
    private:
        Sprite tileSet;

        int rows;
        int columns;

        int tileWidth;
        int tileHeight;

        unsigned int nTiles;         //inserido para não recalcular toda vez
};

#endif