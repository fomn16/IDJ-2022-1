#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Component.hpp"
#include "Timer.hpp"

#include <string>

class Sprite : public Component{
    public: 
        Sprite(GameObject& associated);
        Sprite(GameObject& associated, std::string file, int frameCount = 1, float frameTime=0.1, float secondsToSelfDestruct = 0);
        ~Sprite();
        void Open(std::string file);
        void SetClip (int x, int y, int w, int h);
        void SetClipByIndex (int id);            //adicionado para organizar troca de frames
        void Render ();
        void Render (int x, int y);
        int GetWidth();
        int GetHeight();
        bool IsOpen();

        void SetScaleX(float scaleX, float scaleY);
        Vec2 GetScale();

        void Update(float dt);
        bool Is(std::string type);

        void SetFrame(int frame);
        void SetFrameCount(int frameCount);
        void SetFrameTime(float frameTime);
    private:
        SDL_Texture* texture;
        int width;
        int height;
        SDL_Rect clipRect;

        Vec2 scale;

        int frameCount;
        int currentFrame;
        float timeElapsed;
        float frameTime;

        Timer selfDestructCount;
        float secondsToSelfDestruct;
};

#endif