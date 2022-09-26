#include "TitleState.hpp"
#include "StageState.hpp"
#include "Game.hpp"
#include "GameObject.hpp"
#include "Sprite.hpp"
#include "Text.hpp"

TitleState::TitleState(){
	inputManager = &InputManager::GetInstance();
    LoadAssets();
}

TitleState::~TitleState(){
    objectArray.clear();
}

void TitleState::LoadAssets(){
    //criando Objeto do background
    GameObject* titleBackground = new GameObject();
    //carregando sprite background
    new Sprite(*titleBackground, "assets/img/title.jpg");
    //salvando no object array
    this->AddObject(titleBackground);

    //criando objeto to texto
    GameObject* titleText = new GameObject();
    titleText->box.x = WIDTH/2;
    titleText->box.y = HEIGHT/2 + 100;
    //carregando texto
    new Text(*titleText,"assets/font/Call_me_maybe.ttf", 40, Text::SOLID, "Press spacebar to Start", {255,0,0,0});
    //salvando no object array
    this->AddObject(titleText);
}

void TitleState::Update(float dt){
    if(inputManager->QuitRequested() || inputManager->KeyPress(ESCAPE_KEY))
		quitRequested = true;

    if(inputManager->KeyPress(SPACE_KEY)){
        Game::GetInstance().Push((State*) (new StageState()));
        popRequested = true;
    }

    //fazendo update do timer do texto
    textBlinkTimer.Update(dt);
    if(textBlinkTimer.Get()>0.25){
        textEnabled = !textEnabled;
        textBlinkTimer.Restart();
    }

    UpdateArray(dt);
}

void TitleState::RenderArray(){
    for (int i = 0; i < (int)objectArray.size(); i++){
        //só renderiza o texto se textEnabled
        if(objectArray[i].get()){
            if((objectArray[i].get()->GetComponent("Text") == nullptr) || textEnabled){
                objectArray[i]->Render();
            }
        }
    }
}

void TitleState::Render(){
    RenderArray();
}

void TitleState::Start(){
    StartArray();
}

void TitleState::Pause(){

}

void TitleState::Resume(){

}
