#include "Component.hpp"
#include "GameObject.hpp"

Component::Component(GameObject& associated) : associated(associated){
    associated.AddComponent(this);
}
Component::~Component(){
}
void Component::Update(float dt){}
void Component::Render(){}
void Component::Start(){}
void Component::NotifyCollision(GameObject& other){}