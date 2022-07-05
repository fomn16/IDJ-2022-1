#include "Game.hpp"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"

#include <iostream>

Game* Game::instance;

Game::Game(const char* title, int width, int height){
    //verifica se o game foi inicializado duas vezes
    if(instance != nullptr){
        std::cout<<"Erro: Singleton Game inicializado duas vezes";
        exit(1);
    }

    //inicializa a biblioteca SDL
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)){
        std::cout<<SDL_GetError();
        exit(1);
    }

    //inicializa a biblioteca de imagens
    if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF) != (IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF)){
        std::cout<<"Erro ao inicializar a biblioteca de imagens";
        exit(1);
    }
    
    //inicializa a biblioteca de audio
    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)){
        std::cout<<"Erro ao inicializar a biblioteca de audio";
        exit(1);
    }

    //Aloca canais de audio
    if(Mix_AllocateChannels(32)){
        std::cout<<"Erro ao alocar canais de audio";
        exit(1);
    }

    //instancia janela
    this->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (this->window == nullptr){
        std::cout<<"Erro ao criar janela";
        exit(1);
    }

    //instancia renderizador
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
    if (this->renderer == nullptr){
        std::cout<<"Erro ao instanciar renderizador";
        exit(1);
    }

    //instancia state
    this->state = new State();

    //atribui this à instancia de Game
    instance = this;
}

Game& Game::GetInstance(){
    if(instance == nullptr)
        new Game("joguinho",250,250);
    return *instance;
}

 Game::~Game(){
    //TODO Destroi state
    //this->state->QuitRequested();

    //encerra MIX
    Mix_CloseAudio();
    Mix_Quit();

    //encerra IMG
    IMG_Quit();

    //destrui renderizador e janela
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);

    //encerra SDL
    SDL_Quit();
 }

 State& Game::GetState(){
    return *(this->state);
 }

 SDL_Renderer* Game::GetRenderer(){
    return this->renderer;
 }

 void Game::Run(){
    while(!this->state->QuitRequested()){
        this->state->Update(1f);            //TODO passar dt
        this->state->Render();
        SDL_RenderPresent(this->renderer);
        SDL_Delay(33);
    }
 }