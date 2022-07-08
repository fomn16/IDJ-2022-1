#include "GameObject.hpp"

GameObject::GameObject(){
    isDead = false;
}

GameObject::~GameObject(){
    for(Component* c : components) {
        c->~Component();
    }
    components.clear();
}

void GameObject::Update(float dt){
    for(Component* c : components) {
        c->Update(dt);
    }
}

void GameObject::Render(){
    for(Component* c : components) {
        c->Render();
    }
}

bool GameObject::IsDead(){
    return isDead;
}

void GameObject::RequestDelete(){
    isDead = true;
}

void GameObject::AddComponent(Component* cpt){
    components.push_back(cpt);
}

void GameObject::RemoveComponent(Component* cpt){
    for (int i = 0; i < (int)components.size(); i++){
        if(components[i] == cpt){
            components.erase(i + components.begin());
        }
    }
}

Component* GameObject::GetComponent(std::string type){
    for (int i = 0; i < (int)components.size(); i++){
        if(components[i]->Is(type)){
            return components[i];
        }
    }
    return nullptr;
}
