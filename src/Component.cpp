#include "Component.hpp"
#include "GameObject.hpp"

Component::Component(GameObject& associated) : associated(associated){
    associated.AddComponent(this);
}
Component::~Component(){
}