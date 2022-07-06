#ifndef __MUSIC_H__
#define __MUSIC_H__

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include <string>

class Music{
    public: 
        Music();
        Music(std::string file);
        ~Music();
        void Play(int times = -1);
        void Stop(int msToStop = 1500);
        void Open(std::string file);
        bool IsOpen();
    private:
        Mix_Music* music;
};

#endif