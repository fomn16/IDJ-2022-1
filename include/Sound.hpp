#ifndef __SOUND_H__
#define __SOUND_H__

#include "Component.hpp"
#include "GameObject.hpp"

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"
#include <string>

class Sound : public Component{
    public:
        Sound(GameObject& associated);
        Sound(GameObject& associated, std::string file);
        ~Sound();

        void Play(int times = 1);
        void Stop();
        void Open(std::string file);
        bool IsOpen();

        void Update(float dt);
        void Render();
        bool Is(std::string type);
    private:
        Mix_Chunk*  chunk;
        int channel;
};
#endif