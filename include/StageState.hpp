#ifndef __STAGE_STATE_H__
#define __STAGE_STATE_H__

#include "SDL2/SDL.h"
#include "Sprite.hpp"
#include "Music.hpp"
#include "InputManager.hpp"
#include "GameObject.hpp"
#include "Camera.hpp"
#include "State.hpp"

#include <memory>
#include <vector>

class StageState : public State{
    public:
        StageState();
        ~StageState();

        void LoadAssets();
        void Update(float dt);
        void Render();

        void Start();
        void Pause();
        void Resume();

    private:
        Music backgroundMusic;
        InputManager* inputManager;                         //adicionando referência evitando GetInstace todo frame 
};  

#endif