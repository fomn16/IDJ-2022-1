#include "TileSet.hpp"

TileSet::TileSet(GameObject& associated, int tileWidth, int tileHeight, std::string file) : Component::Component(associated), tileSet(associated, file){
    this->tileWidth = tileWidth;
    this->tileHeight = tileHeight;

    rows = tileSet.GetHeight() / tileHeight;
    columns = tileSet.GetWidth() / tileWidth;

    nTiles = rows * columns;
}

void TileSet::RenderTile(int index, int x, int y){
    if(index < (int)nTiles){
        tileSet.SetClip((index % columns) * tileWidth, (index / columns) * tileHeight, tileWidth, tileHeight);
        tileSet.Render(x, y);
    }
}  

int TileSet::GetTileWidth(){
    return tileWidth;
}

int TileSet::GetTileHeight(){
    return tileHeight;
}

bool TileSet::Is(std::string type){
    return !type.compare("TileSet");
}

void TileSet::Render(){}
void TileSet::Update(float dt){}