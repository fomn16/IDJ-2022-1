#include "TileMap.hpp"
#include <fstream>

TileMap::TileMap(GameObject& associated, std::string file, TileSet* tileSet) : Component::Component(associated), tileSet(tileSet)
{
    Load(file);
}

void TileMap::Load(std::string file){
    std::ifstream tileFile;
    tileFile.open(file);

    if(!tileFile){
        std::ofstream fw("logs.txt", std::ofstream::out);
        fw<<"Erro: arquivo de tileMap não carregado";
        fw.close();
        exit(1);
    }

    char ignore;
    int tileIndex;

    tileFile >> mapWidth >> ignore >> mapHeight >> ignore >> mapDepth;

    for (int i = 0; i < mapWidth * mapHeight * mapDepth; i++){
        tileFile >> ignore >> tileIndex;
        tileMatrix.push_back(tileIndex - 1);
    }
}

void TileMap::SetTileSet(TileSet* tileSet){
    this->tileSet = tileSet;
}

int& TileMap::At(int x, int y, int z){
    return tileMatrix[x + mapWidth*y + mapWidth*mapHeight*z];
}

void TileMap::Render(){
    for (int i = 0; i < mapDepth; i++){
        RenderLayer(i);
    }
}


void TileMap::RenderLayer(int layer, int cameraX, int cameraY){
    int tileW = tileSet->GetTileWidth();
    int tileH = tileSet->GetTileHeight();
    int tileIndex;

    for(int i = 0; i < mapWidth; i++){
        for (int j = 0; j < mapHeight; j++){
            tileIndex = At(i, j, layer);
            if(tileIndex >= 0){
                tileSet->RenderTile(tileIndex, i*tileW - cameraX, j*tileH - cameraY);
            }
        }
    }
}

int TileMap::GetWidth(){
    return mapWidth;
}

int TileMap::GetHeight(){
    return mapHeight;
}

int TileMap::GetDepth(){
    return mapDepth;
}

bool TileMap::Is(std::string type){
    return !type.compare("TileMap");
}

void TileMap::Update(float dt){}