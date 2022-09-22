#include "TileSet.hpp"
#include <iostream>

TileSet::TileSet(GameObject& associated, int tileWidth, int tileHeight, std::string file) : Component::Component(associated){
    new Sprite(associated,file);
    this->tileWidth = tileWidth;
    this->tileHeight = tileHeight;
    rows = ((Sprite*)associated.GetComponent("Sprite"))->GetHeight() / tileHeight;
    columns = ((Sprite*)associated.GetComponent("Sprite"))->GetWidth() / tileWidth;

    nTiles = rows * columns;
}

void TileSet::RenderTile(int index, int x, int y){
    if(index < (int)nTiles){
        ((Sprite*)associated.GetComponent("Sprite"))->SetClip((index % columns) * tileWidth, (index / columns) * tileHeight, tileWidth, tileHeight);
        ((Sprite*)associated.GetComponent("Sprite"))->Render(x, y);
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