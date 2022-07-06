#include "State.hpp"

State::State(){
    QuitRequested();
    LoadAssets();
}

bool State::QuitRequested(){
    return quitRequested;
}
void State::LoadAssets(){
    //Deixe para carregar imagens/fontes/músicas às suas variáveis aqui sempre que for possível

    //carregando o sprite de background
    bg.Open("assets/img/ocean.jpg");

    //carregando e dando play na música 
    music.Open("assets/audio/stageState.ogg");
    music.Play();
}
void State::Update(float dt){
    if(SDL_QuitRequested())
        quitRequested = true;
}
void State::Render(){
    bg.Render(0,0);
}