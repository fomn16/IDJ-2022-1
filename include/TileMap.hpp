#ifndef __TILEMAP_H__
#define __TILEMAP_H__

#include "GameObject.hpp"
#include "Component.hpp"
#include "TileSet.hpp"

#include <string>
#include <vector>

class TileMap : public Component{
    public:
        TileMap(GameObject& associated, std::string file);
        void Load(std::string file);
        int& At(int x, int y, int z = 0);
        void Render();
        void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);
        int GetWidth();
        int GetHeight();
        int GetDepth();

        bool Is(std::string type);

    private:
        std::vector<int> tileMatrix;
        int mapWidth;
        int mapHeight;
        int mapDepth;
};

#endif