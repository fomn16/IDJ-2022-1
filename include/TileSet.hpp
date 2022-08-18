#ifndef __TILESET_H__
#define __TILESET_H__

#include <string>

#include "Sprite.hpp"
#include "GameObject.hpp"

//Escolhi fazer com que TileSet seja um componente
class TileSet : public Component{
    public:
        TileSet(GameObject& associated, int tileWidth, int tileHeight, std::string file);
        void RenderTile(int index, int x, int y);
        int GetTileWidth();
        int GetTileHeight();

        bool Is(std::string type);
        void Render();
        void Update(float dt);
        void Start();
    private:
        Sprite tileSet;

        int rows;
        int columns;

        int tileWidth;
        int tileHeight;

        unsigned int nTiles;         //inserido para não recalcular toda vez
};

#endif