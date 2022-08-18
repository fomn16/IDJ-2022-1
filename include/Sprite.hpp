#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Component.hpp"

#include <string>

class Sprite : public Component{
    public: 
        Sprite(GameObject& associated);
        Sprite(GameObject& associated, std::string file);
        ~Sprite();
        void Open(std::string file);
        void SetClip (int x, int y, int w, int h);
        void Render ();
        void Render (int x, int y);
        int GetWidth();
        int GetHeight();
        bool IsOpen();

        void Update(float dt);
        bool Is(std::string type);
        void Start();
    private:
        SDL_Texture* texture;
        int width;
        int height;
        SDL_Rect clipRect;
};

#endif