#include "Face.hpp"
#include "Sound.hpp"

Face::Face(GameObject& associated) : Component::Component(associated){
    hitpoints = 30;
    inputManager = &InputManager::GetInstance();
}

void Face::Damage(int damage){
    hitpoints -= damage;
    if (hitpoints <= 0){
        Sound* sound = (Sound*) associated.GetComponent("Sound");
        if(sound != nullptr){
           sound->Play();
        }
        associated.RequestDelete();
    }
}

void Face::Update(float dt){
    if(inputManager->MousePress(LEFT_MOUSE_BUTTON)){
        if(associated.camera != nullptr){
            if(associated.box.Contains( {(float)inputManager->GetMouseX() + associated.camera->pos.x, (float)inputManager->GetMouseY() + associated.camera->pos.y} ) ) {
                // Aplica dano
                Damage(std::rand() % 10 + 10);
            }
        }
        else{
            if(associated.box.Contains( {(float)inputManager->GetMouseX(), (float)inputManager->GetMouseY()} ) ) {
                // Aplica dano
                Damage(std::rand() % 10 + 10);
            }
        } 
    }
    //atualiza a posição de seu objeto
}

void Face::Render(){

}

bool Face::Is(std::string type){
    return !type.compare("Face");
}

