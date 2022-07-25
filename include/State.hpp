#ifndef __STATE_H__
#define __STATE_H__

#include "SDL2/SDL.h"
#include "Sprite.hpp"
#include "Music.hpp"
#include "InputManager.hpp"
#include "GameObject.hpp"
#include "Camera.hpp"

#include <memory>
#include <vector>

class State{
    public:
        State();
        ~State();
        bool QuitRequested();
        void LoadAssets();
        void Update(float dt);
        void Render();

    private:
        void AddObject(int mouseX, int mouseY);
        
        Music music;
        bool quitRequested;
        std::vector<std::unique_ptr<GameObject>> objectArray;
        InputManager* inputManager;                         //adicionando referência evitando GetInstace todo frame
        Camera camera;
};  

#endif