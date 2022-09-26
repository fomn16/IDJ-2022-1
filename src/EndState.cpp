#include "EndState.hpp"
#include "GameData.hpp"
#include "InputManager.hpp"
#include "Sprite.hpp"
#include "Game.hpp"
#include "Text.hpp"
#include "StageState.hpp"

EndState::EndState(){
	inputManager = &InputManager::GetInstance();
    LoadAssets();
}

EndState::~EndState(){
    objectArray.clear();
}

void EndState::LoadAssets(){
    std::string bg = "assets/img/win.jpg";
    std::string mus = "assets/audio/endStateWin.ogg";
    if(!GameData::playerVictory){
        bg = "assets/img/lose.jpg";
        mus = "assets/audio/endStateLose.ogg";
    }
    //criando Objeto do background
    GameObject* endBackground = new GameObject();
    //carregando sprite background
    new Sprite(*endBackground, bg);
    //salvando no object array
    this->AddObject(endBackground);

    //carregando e dando play na música 
    backgroundMusic.Open(mus);
    //backgroundMusic.Play();

    //criando objeto dos textos
    GameObject* texts = new GameObject();
    texts->box.x = WIDTH/2;
    texts->box.y = 100;
    //carregando texto
    new Text(*texts,"assets/font/Call_me_maybe.ttf", 40, Text::SOLID, "Press spacebar to Restart\nPress ESC to Quit", {255,0,0,0});
    //salvando no object array
    this->AddObject(texts);
}

void EndState::Update(float dt){
    if(inputManager->QuitRequested() || inputManager->KeyPress(ESCAPE_KEY))
		quitRequested = true;

    if(inputManager->KeyPress(SPACE_KEY)){
        Game::GetInstance().Push((State*) (new StageState()));
        popRequested = true;
    }

    UpdateArray(dt);
}

void EndState::Render(){
    RenderArray();
}

void EndState::Start(){
    StartArray();
    backgroundMusic.Play();
    started = true;
}

void EndState::Pause(){
    backgroundMusic.Stop(0);
}

void EndState::Resume(){
    backgroundMusic.Play();
}