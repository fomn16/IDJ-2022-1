#include "StageState.hpp"
#include "Vec2.hpp"
#include "Face.hpp"
#include "Sound.hpp"
#include "TileMap.hpp"
#include "TileSet.hpp"
#include "Alien.hpp"
#include <math.h>
#include "PenguinBody.hpp"
#include "Collision.hpp"
#include "Collider.hpp"
#include "Game.hpp"
#include "TitleState.hpp"
#include "GameData.hpp"
#include "EndState.hpp"

#include <iostream>
#include <fstream>

StageState::StageState(){
	inputManager = &InputManager::GetInstance();
    LoadAssets();
}

StageState::~StageState(){
    objectArray.clear();
}

void StageState::LoadAssets(){
    //Deixe para carregar imagens/fontes/músicas às suas variáveis aqui sempre que for possível
	
    //criando objeto background
    GameObject* background = new GameObject();

    //carregando sprite background
    new Sprite(*background, "assets/img/ocean.jpg");

    //salvando no object array
    this->AddObject(background);

	//criando objeto tileMap
	GameObject* tileMapObject = new GameObject(&Game::GetInstance().camera);

	//criando tileSet
	new TileSet(*tileMapObject, 64, 64, "assets/img/tileset.png");
    
	//criando componente tileMap
	new TileMap(*tileMapObject, "assets/map/tileMap.txt");

	//salvando no object array
    this->AddObject(tileMapObject);

    //carregando e dando play na música 
    backgroundMusic.Open("assets/audio/stageState.ogg");
    //backgroundMusic.Play();

    //criando aliens
    for (int i=0; i < N_ALIENS; i++){
        //Criando objeto Alien
        GameObject* alienObject = new GameObject(&Game::GetInstance().camera);
        
        //criando alien
        new Alien(*alienObject, 10, i);
        alienObject->box.SetCenter(Vec2(std::rand() % MAP_WIDTH, std::rand() % MAP_HEIGHT));

        //salvando no object array
        this->AddObject(alienObject);
    }

    //Criando objeto Penguim
    GameObject* penguinObject = new GameObject(&Game::GetInstance().camera);

    //criando Penguim
    new PenguinBody(*penguinObject);
    penguinObject->box.SetCenter(Vec2(704, 640));

    //salvando no object array
    this->AddObject(penguinObject);
}

void StageState::Update(float dt){
    Game::GetInstance().camera.Update(dt);
    if(inputManager->QuitRequested())
		quitRequested = true;
    if(inputManager->KeyPress(ESCAPE_KEY)){
        Game::GetInstance().Push((State*) (new TitleState()));
        popRequested = true;
    }

    UpdateArray(dt);

    //calculando colisões

    std::vector<std::shared_ptr<GameObject>> colliderObjects;
    for (int i = 0; i < (int)objectArray.size(); i++){
        if(objectArray[i]->GetComponent("Collider") != nullptr)
            colliderObjects.push_back(objectArray[i]);
    }

    Rect rect1,rect2;
    float angle1,angle2;
    for (int i = 0; i < (int)colliderObjects.size() - 1; i++){
        rect1 = ((Collider*)colliderObjects[i]->GetComponent("Collider"))->box;
        angle1 = colliderObjects[i]->angleDeg;
        for (int j = i+1; j < (int)colliderObjects.size(); j++){
            rect2 = ((Collider*)colliderObjects[j]->GetComponent("Collider"))->box;
            angle2 = colliderObjects[j]->angleDeg;
            if(Collision::IsColliding(rect1, rect2, angle1, angle2))
            {
                colliderObjects[i]->NotifyCollision(*colliderObjects[j].get());
                colliderObjects[j]->NotifyCollision(*colliderObjects[i].get());
            }
        }
    }


    //esperando todos os sons acabarem de tocar para fechar o estado
    bool isSoundPlaying = false;

    for (int i = 0; i < (int)objectArray.size(); i++){
        if(objectArray[i]->GetComponent("Sound") != nullptr)
            isSoundPlaying = true;
    }


    if((PenguinBody::player == nullptr || Alien::alienCount == 0) && !isSoundPlaying){
        GameData::playerVictory = Alien::alienCount == 0;
        Game::GetInstance().Push((State*) (new EndState()));
        popRequested = true;
    }
 }

void StageState::Render(){
    RenderArray();
}

void StageState::Start(){
    StartArray();
    backgroundMusic.Play();
    started = true;
}

void StageState::Pause(){
    backgroundMusic.Stop(0);
}

void StageState::Resume(){
    backgroundMusic.Play();
}