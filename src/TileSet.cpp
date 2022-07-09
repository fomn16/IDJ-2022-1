#include "TileSet.hpp"

TileSet::TileSet(GameObject& associated, int tileWidth, int tileHeight, std::string file) : tileSet(associated, file){
    this->tileWidth = tileWidth;
    this->tileHeight = tileHeight;

    rows = tileSet.GetHeight() / tileHeight;
    columns = tileSet.GetWidth() / tileWidth;

    nTiles = rows * columns;
}

void TileSet::RenderTile(unsigned int index, float x, float y){
    if(index < nTiles){
        tileSet.SetClip(index % columns, index / rows, tileWidth, tileHeight);
        tileSet.Render((int)x, (int)y);
    }
}  

int TileSet::GetTileWidth(){
    return tileWidth;
}

int TileSet::GetTileHeight(){
    return tileHeight;
}
