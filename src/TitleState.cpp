#include "TitleState.hpp"
#include "StageState.hpp"
#include "Game.hpp"
#include "GameObject.hpp"
#include "Sprite.hpp"

TitleState::TitleState(){
	inputManager = &InputManager::GetInstance();
}

void TitleState::LoadAssets(){
     GameObject* titleScreen = new GameObject();

    //carregando sprite background
    new Sprite(*titleScreen, "assets/img/title.jpg");
    //salvando no object array
    this->AddObject(titleScreen);
}

void TitleState::Update(float dt){
    if(inputManager->QuitRequested() || inputManager->KeyPress(ESCAPE_KEY))
		quitRequested = true;

    if(inputManager->KeyPress(SPACE_KEY)){
        Game::GetInstance().Push((State*) (new StageState()));
        popRequested = true;
    }

    UpdateArray(dt);
}

void TitleState::Render(){
    RenderArray();
}

void TitleState::Start(){
    LoadAssets();
    StartArray();
}

void TitleState::Pause(){

}

void TitleState::Resume(){

}
