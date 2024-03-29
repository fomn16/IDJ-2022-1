#include "GameObject.hpp"

GameObject::GameObject(){
    isDead = false;
}

GameObject::GameObject(Camera* camera) : GameObject(){
    isDead = false;
    this->camera = camera;
}

GameObject::~GameObject(){
    components.clear();
}

void GameObject::Update(float dt){
    for(int i = 0; i < (int)components.size(); i++) {
        components[i]->Update(dt);
    }
}

void GameObject::Render(){
    for(int i = 0; i < (int)components.size(); i++) {
        components[i]->Render();
    }
}

bool GameObject::IsDead(){
    return isDead;
}

void GameObject::RequestDelete(){
    isDead = true;
}

void GameObject::AddComponent(Component* cpt){
    components.push_back((std::unique_ptr<Component>)cpt);
    if(started)
        cpt->Start();
}

void GameObject::RemoveComponent(Component* cpt){
    for (int i = (int)components.size() - 1; i > 0; i--){
        if(components[i].get() == cpt){
            components.erase(i + components.begin());
        }
    }
}

Component* GameObject::GetComponent(std::string type){
    for (int i = 0; i < (int)components.size(); i++){
        if(components[i]->Is(type)){
            return components[i].get();
        }
    }
    return nullptr;
}

void GameObject::Start(){
    for(int i = 0; i < (int)components.size(); i++) {
        components[i]->Start();
    }
    started = true;
}

void GameObject::NotifyCollision(GameObject& other){
    for (int i = 0; i < (int)components.size(); i++){
        components[i]->NotifyCollision(other);
    }
}