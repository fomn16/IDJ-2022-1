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
        void Start();
        std::weak_ptr<GameObject> AddObject(GameObject* go);
        std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);

    private:
        void AddObject(int mouseX, int mouseY);
        
        Music music;
        bool quitRequested;
        std::vector<std::shared_ptr<GameObject>> objectArray;
        InputManager* inputManager;                         //adicionando referência evitando GetInstace todo frame
        Camera camera;
        bool started = false;
        
};  

#endif