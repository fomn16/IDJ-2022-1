#ifndef __TITLE_STATE_H__
#define __TITLE_STATE_H__

#include "State.hpp"
#include "InputManager.hpp"

class TitleState : public State{
    public:
        TitleState();

        void LoadAssets();
        void Update(float dt);
        void Render();

        void Start();
        void Pause();
        void Resume();

    private:
        InputManager* inputManager;                         //adicionando referência evitando GetInstace todo frame 
};

#endif