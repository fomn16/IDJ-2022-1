#ifndef __GAME_H__
#define __GAME_H__
#include "SDL2/SDL.h"
#include "State.hpp"
#include "InputManager.hpp"
#include <string>

class Game{
    private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    static Game* instance;
    State* state;
    InputManager* inputManager;                         //adicionando referência evitando GetInstace todo frame
    Game (std::string title, int width, int height);

    int frameStart = 0;
    float dt = 0;
    void CalculateDeltaTime();

    public:
    ~Game();
    void Run();
    SDL_Renderer* GetRenderer();
    State& GetState();
    static Game& GetInstance();
    float GetdeltaTime();
};
#endif