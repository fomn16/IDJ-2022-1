#ifndef __END_STATE_H__
#define __END_STATE_H__

#include "State.hpp"
#include "Music.hpp"
#include "InputManager.hpp"

class EndState : public State{
    public:
        EndState();
        ~EndState();

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