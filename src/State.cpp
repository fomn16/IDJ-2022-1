#include "State.hpp"
#include "Vec2.hpp"
#include "Face.hpp"
#include "Sound.hpp"
#include "TileMap.hpp"
#include "TileSet.hpp"
#include "Alien.hpp"
#include <math.h>
#include "PenguinBody.hpp"


#include <iostream>
#include <fstream>

State::State(){
	inputManager = &InputManager::GetInstance();
    QuitRequested();
}

State::~State(){
    objectArray.clear();
}

bool State::QuitRequested(){
    return quitRequested;
}

void State::LoadAssets(){
    //Deixe para carregar imagens/fontes/músicas às suas variáveis aqui sempre que for possível
	
    //criando objeto background
    GameObject* background = new GameObject();

    //carregando sprite background
    new Sprite(*background, "assets/img/ocean.jpg");

    //salvando no object array
    this->AddObject(background);

	//criando objeto tileMap
	GameObject* tileMapObject = new GameObject(&camera);

	//criando tileSet
	TileSet* tileSet = new TileSet(*tileMapObject, 64, 64, "assets/img/tileset.png");

	//criando componente tileMap
	new TileMap(*tileMapObject, "assets/map/tileMap.txt", tileSet);

	//salvando no object array
    this->AddObject(tileMapObject);

    //carregando e dando play na música 
    music.Open("assets/audio/stageState.ogg");
    music.Play();

    //Criando objeto Alien
    GameObject* alienObject = new GameObject(&camera);

    //criando alien
    new Alien(*alienObject, 10);
    alienObject->box.SetCenter(Vec2(512,300));

    //salvando no object array
    this->AddObject(alienObject);

    //Criando objeto Penguim
    GameObject* penguinObject = new GameObject(&camera);

    //criando Penguim
    new PenguinBody(*penguinObject);
    penguinObject->box.SetCenter(Vec2(704, 640));

    //salvando no object array
    this->AddObject(penguinObject);

}

void State::Update(float dt){
    camera.Update(dt);
    if(inputManager->QuitRequested() || inputManager->KeyPress(ESCAPE_KEY))
		quitRequested = true;

	if(inputManager->KeyPress(SPACE_KEY)){
        Vec2 objPos = Vec2( 200, 0 ).GetRotated( -M_PI + M_PI*(rand() % 1001)/500.0 ) + Vec2( inputManager->GetMouseX(), inputManager->GetMouseY() );
        AddObject((int)objPos.x, (int)objPos.y);
    }

    for (int i = 0; i < (int)objectArray.size(); i++){
        objectArray[i]->Update(dt);
    }
    for (int i = 0; i < (int)objectArray.size(); i++){
        if(objectArray[i]->IsDead()){
            objectArray.erase(objectArray.begin() + i);
        }
    }
}

void State::Render(){
    for (int i = 0; i < (int)objectArray.size(); i++){
        objectArray[i]->Render();
    }
}

void State::AddObject(int mouseX, int mouseY){
    //criando objeto inimigo
    GameObject* inimigo = new GameObject(&camera);
    inimigo->box.x = mouseX + camera.pos.x;
    inimigo->box.y = mouseY + camera.pos.y;

    //carregando sprite inimigo
    new Sprite(*inimigo, "assets/img/penguinface.png");

    //carregando som inimigo
    new Sound(*inimigo, "assets/audio/boom.wav");

    //carregando comportamento inimigo
    new Face(*inimigo);

    this->AddObject(inimigo);
}

void State::Start(){
    LoadAssets();
    for (int i = 0; i < (int)objectArray.size(); i++){
        objectArray[i]->Start();
    }
    started = true;
}

std::weak_ptr<GameObject> State::AddObject(GameObject* go){
    std::shared_ptr<GameObject> pointer(go);
    objectArray.push_back(pointer);
    if(started)
        pointer->Start(); 
    std::weak_ptr<GameObject> weak_pointer(pointer);
    return weak_pointer;
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go){
     for (int i = 0; i < (int)objectArray.size(); i++){
        if(objectArray[i].get() == go)
        {
            std::weak_ptr<GameObject> weak_pointer(objectArray[i]);
            return weak_pointer;
        }
    }
    std::weak_ptr<GameObject> weak_pointer;
    return weak_pointer;
}