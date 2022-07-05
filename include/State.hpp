#ifndef __STATE_H__
#define __STATE_H__

#include "SDL2/SDL.h"

class Sprite{
    public: Sprite();
};
class Music{
    public: Music();
};

class State{
    public:
    State();
    bool QuitRequested();
    void LoidAssets();
    void Update(float dt);
    void Render();

    private:
    Sprite bg;
    Music music;
    bool quitRequested;
};  

#endif