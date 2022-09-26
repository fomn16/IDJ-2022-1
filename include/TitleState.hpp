#ifndef __TITLE_STATE_H__
#define __TITLE_STATE_H__

#include "State.hpp"
#include "InputManager.hpp"
#include "Timer.hpp"

class TitleState : public State{
    public:
        TitleState();
        ~TitleState();

        void LoadAssets();
        void Update(float dt);
        void Render();
        void RenderArray();

        void Start();
        void Pause();
        void Resume();

    private:
        Timer textBlinkTimer;
        bool textEnabled = true;
        InputManager* inputManager;                         //adicionando referência evitando GetInstace todo frame 
};

#endif