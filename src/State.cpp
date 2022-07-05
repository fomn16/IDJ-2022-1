#include "State.hpp"

//TODO tirar daqui
Music::Music(){}

State::State(){
    QuitRequested();
    LoadAssets();
}

bool State::QuitRequested(){
    return quitRequested;
}
void State::LoadAssets(){
    //Deixe para carregar imagens/fontes/músicas às suas variáveis aqui sempre que for possível
    bg.Open("assets/img/ocean.jpg");        //carregando o sprite de background
}
void State::Update(float dt){
    if(SDL_QuitRequested())
        quitRequested = true;
}
void State::Render(){
    bg.Render(0,0);
}