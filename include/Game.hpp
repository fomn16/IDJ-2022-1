#ifndef __GAME_H__
#define __GAME_H__
#include "SDL2/SDL.h"
#include "State.hpp"
#include <string>

class Game{
    private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    static Game* instance;
    State* state;
    Game (std::string title, int width, int height);

    public:
    ~Game();
    void Run();
    SDL_Renderer* GetRenderer();
    State& GetState();
    static Game& GetInstance();
};
#endif