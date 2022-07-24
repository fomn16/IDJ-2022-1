#include "State.hpp"
#include "Vec2.hpp"
#include "Face.hpp"
#include "Sound.hpp"
#include "TileMap.hpp"
#include "TileSet.hpp"
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
    objectArray.emplace_back(background);

	//criando objeto tileMap
	GameObject* tileMapObject = new GameObject();

	//criando tileSet
	TileSet* tileSet = new TileSet(*tileMapObject, 64, 64, "assets/img/tileset.png");
	tileMapObject->AddComponent(tileSet);

	//criando componente tileMap
	TileMap* tileMap = new TileMap(*tileMapObject, "assets/map/tileMap.txt", tileSet);
	tileMapObject->AddComponent(tileMap);

	//salvando no object array
	objectArray.emplace_back(tileMapObject);

    //carregando e dando play na música 
    music.Open("assets/audio/stageState.ogg");
    music.Play();
}
void State::Update(float dt){
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
    GameObject* inimigo = new GameObject();
    inimigo->box.x = mouseX;
    inimigo->box.y = mouseY;

    //carregando sprite inimigo
    Sprite* spriteInimigo = new Sprite(*inimigo, "assets/img/penguinface.png");
    inimigo->AddComponent(spriteInimigo);

    //carregando som inimigo
    Sound* somInimigo = new Sound(*inimigo, "assets/audio/boom.wav");
    inimigo->AddComponent(somInimigo);

    //carregando comportamento inimigo
    Face* compInimigo = new Face(*inimigo);
    inimigo->AddComponent(compInimigo);

    objectArray.emplace_back(inimigo);
}