#include "Face.hpp"
#include "Sound.hpp"

Face::Face(GameObject& associated) : Component::Component(associated){
    hitpoints = 30;
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

}

void Face::Render(){

}

bool Face::Is(std::string type){
    return !type.compare("Face");
}

