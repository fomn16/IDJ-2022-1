#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class Sprite{
    public: 
        Sprite();
        Sprite(const char* file);
        ~Sprite();
        void Open(const char* file);
        void SetClip (int x, int y, int w, int h);
        void Render (int x, int y);
        int GetWidth();
        int GetHeight();
        bool IsOpen();
    private:
        SDL_Texture* texture;
        int width;
        int height;
        SDL_Rect clipRect;
};

#endif