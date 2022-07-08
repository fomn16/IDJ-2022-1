#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Component.hpp"
#include <string>

class Sprite : public Component{
    public: 
        Sprite(GameObject& associated);
        Sprite(GameObject& associated, const char* file);
        ~Sprite();
        void Open(const char* file);
        void SetClip (int x, int y, int w, int h);
        void Render ();
        int GetWidth();
        int GetHeight();
        bool IsOpen();

        void Update(float dt);
        bool Is(std::string type);
    private:
        SDL_Texture* texture;
        int width;
        int height;
        SDL_Rect clipRect;
};

#endif