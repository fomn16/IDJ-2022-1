#ifndef __GAME_H__
#define __GAME_H__
#include "SDL2/SDL.h"
#include "State.hpp"
#include "InputManager.hpp"
#include <string>
#include <stack>

#define WIDTH 1024
#define HEIGHT 600

#define MAP_WIDTH 1408
#define MAP_HEIGHT 1280

class Game{
    private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    static Game* instance;
    State* storedState;
    InputManager* inputManager;                         //adicionando referência evitando GetInstace todo frame
    Game (std::string title, int width, int height);

    int frameStart = 0;
    float dt = 0;
    void CalculateDeltaTime();

    std::stack<std::unique_ptr<State>> stateStack;

    public:
    ~Game();
    void Run();
    SDL_Renderer* GetRenderer();
    State& GetCurrentState();
    static Game& GetInstance();
    float GetdeltaTime();

    void Push(State* state);

    Camera camera;
};
#endif