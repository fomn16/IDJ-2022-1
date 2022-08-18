#include "State.hpp"
#include "Vec2.hpp"
#include "Face.hpp"
#include "Sound.hpp"
#include "TileMap.hpp"
#include "TileSet.hpp"
#include "Alien.hpp"
#include <math.h>

State::State(){
	inputManager = &InputManager::GetInstance();
    QuitRequested();
    LoadAssets();
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
    Sprite* spriteBackground = new Sprite(*background, "assets/img/ocean.jpg");
    background->AddComponent(spriteBackground);

    //salvando no object array
    this->AddObject(background);

	//criando objeto tileMap
	GameObject* tileMapObject = new GameObject(&camera);

	//criando tileSet
	TileSet* tileSet = new TileSet(*tileMapObject, 64, 64, "assets/img/tileset.png");
	tileMapObject->AddComponent(tileSet);

	//criando componente tileMap
	TileMap* tileMap = new TileMap(*tileMapObject, "assets/map/tileMap.txt", tileSet);
	tileMapObject->AddComponent(tileMap);

	//salvando no object array
    this->AddObject(tileMapObject);

    //carregando e dando play na música 
    music.Open("assets/audio/stageState.ogg");
    music.Play();

    //Criando objeto Alien
    GameObject* alienObject = new GameObject(&camera);

    //criando alien
    Alien* alien = new Alien(*alienObject, 10);
    alienObject->AddComponent(alien);

    //quando o sprite é carregado, A classe Sprite corrige 
    //a posição para que a box tenha seu centro na sua posição inicial 
    alienObject->box.x = 512;
    alienObject->box.y = 300;

    //salvando no object array
    this->AddObject(alienObject);
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
    Sprite* spriteInimigo = new Sprite(*inimigo, "assets/img/penguinface.png");
    inimigo->AddComponent(spriteInimigo);

    //carregando som inimigo
    Sound* somInimigo = new Sound(*inimigo, "assets/audio/boom.wav");
    inimigo->AddComponent(somInimigo);

    //carregando comportamento inimigo
    Face* compInimigo = new Face(*inimigo);
    inimigo->AddComponent(compInimigo);

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