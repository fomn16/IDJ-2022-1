#include "State.hpp"

//TODO tirar daqui
Music::Music(){}
Sprite::Sprite(){}

State::State(){
    QuitRequested();
    //TODO instanciar o sprite
}

bool State::QuitRequested(){
    return this->quitRequested;
}
void State::LoidAssets(){
    //Deixe para carregar imagens/fontes/músicas às suas variáveis aqui sempre que for possível
}
void State::Update(float dt){
    if(SDL_QuitRequested())
        this->quitRequested = true;
}
void State::Render(){
    //TODO Chamar render background
}