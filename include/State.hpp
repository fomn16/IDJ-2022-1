#ifndef __STATE_H__
#define __STATE_H__

#include "SDL2/SDL.h"
#include "Sprite.hpp"

//TODO tirar daqui
class Music{
    public: Music();
};

class State{
    public:
    State();
    bool QuitRequested();
    void LoadAssets();
    void Update(float dt);
    void Render();

    private:
    Sprite bg;
    Music music;
    bool quitRequested;
};  

#endif