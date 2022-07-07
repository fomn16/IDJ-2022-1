#include "GameObject.hpp"


GameObject::GameObject(){
    isDead = false;
}

GameObject::~GameObject(){

}

void GameObject::Update(float dt){

}

void GameObject::Render(){

}

bool GameObject::IsDead(){

}

void GameObject::RequestDelete(){

}

void GameObject::AddComponent(Component* cpt){

}

void GameObject::RemoveComponent(Component* cpt){

}

Component* GameObject::GetComponent(std::string type){

}
