#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H__
#include "SDL2/SDL.h"
#include <unordered_map>

#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN
#define ESCAPE_KEY SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT

#define SPACE_KEY SDLK_SPACE

class InputManager{
    public:
        void Update();

        bool KeyPress(int key);
        bool KeyRelease(int key);
        bool IsKeyDown(int key);

        bool MousePress(int button);
        bool MouseRelease(int button);
        bool IsMouseDown(int button);

        int GetMouseX();
        int GetMouseY();

        bool QuitRequested();

        static InputManager& GetInstance();

    private:
        InputManager();
        ~InputManager();

        static InputManager instance;

        //achei melhor usar map no mouse também
        std::unordered_map<int, bool> mouseState;
        std::unordered_map<int, int> mouseUpdate;

        std::unordered_map<int, bool> keyState;
        std::unordered_map<int, int> keyUpdate;

        bool quitRequested = 0;

        int updateCounter = 0;

        int mouseX = 0;
        int mouseY = 0;

};

#endif