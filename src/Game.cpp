#include "Game.hpp"
#include "Resources.hpp"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include <iostream>
#include <fstream>

Game* Game::instance = nullptr;

Game::Game(std::string title, int width, int height){
    //verifica se o game foi inicializado duas vezes
    if(Game::instance != nullptr){
        std::ofstream fw("logs.txt", std::ofstream::out);
        fw<<"Erro: Singleton Game inicializado duas vezes";
        fw.close();
        exit(1);
    }
    //atribui this à instancia de Game
    Game::instance = this;

    //inicializa a biblioteca SDL
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)){
        std::ofstream fw("logs.txt", std::ofstream::out);
        fw<<"Erro ao inicializar SDL: "<<SDL_GetError();
        fw.close();
        exit(1);
    }

    //inicializa a biblioteca de imagens
    if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF) == 0 /*!= (IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF)*/){
        std::ofstream fw("logs.txt", std::ofstream::out);
        fw<<"Erro ao inicializar a biblioteca de imagens: " << IMG_GetError();
        fw.close();
        exit(1);
    }
    
    //inicializa a biblioteca de audio
    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)){
        std::ofstream fw("logs.txt", std::ofstream::out);
        fw<<"Erro ao inicializar a biblioteca de audio: " << Mix_GetError();
        fw.close();
        exit(1);
    }

    //Aloca canais de audio
    if(Mix_AllocateChannels(32) != 32){
        std::ofstream fw("logs.txt", std::ofstream::out);
        fw<<"Erro ao alocar canais de audio: " << Mix_GetError();
        fw.close();
        exit(1);
    }

    //instancia janela
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (window == nullptr){
        std::ofstream fw("logs.txt", std::ofstream::out);
        fw<<"Erro ao criar janela";
        fw.close();
        exit(1);
    }

    //instancia renderizador
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr){
        std::ofstream fw("logs.txt", std::ofstream::out);
        fw<<"Erro ao instanciar renderizador";
        fw.close();
        exit(1);
    }
    //instancia state
    state = new State();

    inputManager = &InputManager::GetInstance();

    frameStart = (float)SDL_GetTicks()/1000;
    dt = 0.016;
}

Game& Game::GetInstance(){
    if(Game::instance == nullptr){
        Game::instance = new Game("Felipe Neves",1024,600);
    }
    return *Game::instance;
}

 Game::~Game(){
    //TODO Destroi state
    //state->QuitRequested();

    //encerra MIX
    Mix_CloseAudio();
    Mix_Quit();

    //encerra IMG
    IMG_Quit();

    //destrui renderizador e janela
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    //encerra SDL
    SDL_Quit();
 }

 State& Game::GetState(){
    return *(state);
 }

 SDL_Renderer* Game::GetRenderer(){
    return renderer;
 }

 void Game::Run(){
    while(!state->QuitRequested()){
        inputManager->Update();
        state->Update(dt);
        state->Render();
        SDL_RenderPresent(renderer);
        SDL_Delay(33);
    }

    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();
 }

 
 void Game::CalculateDeltaTime(){
    float currTime = (float)SDL_GetTicks()/1000;
    dt = currTime - frameStart;
    frameStart = currTime;
 }

 float Game::GetdeltaTime(){
    return dt;
 }