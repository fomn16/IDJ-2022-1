#include "State.hpp"

State::State(){

}

State::~State(){
    objectArray.clear();
}

std::weak_ptr<GameObject> State::AddObject(GameObject* object){
    std::shared_ptr<GameObject> pointer(object);
    objectArray.push_back(pointer);
    if(started)
        pointer->Start(); 
    std::weak_ptr<GameObject> weak_pointer(pointer);
    return weak_pointer;
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* object){
     for (int i = 0; i < (int)objectArray.size(); i++){
        if(objectArray[i].get() == object)
        {
            std::weak_ptr<GameObject> weak_pointer(objectArray[i]);
            return weak_pointer;
        }
    }
    std::weak_ptr<GameObject> weak_pointer;
    return weak_pointer;
}

bool State::PopRequested(){
    return popRequested;
}

bool State::QuitRequested(){
    return quitRequested;
}

void State::StartArray(){
    for (int i = 0; i < (int)objectArray.size(); i++){
        objectArray[i]->Start();
    }
}

void State::UpdateArray(float dt){
    for (int i = 0; i < (int)objectArray.size(); i++){
        objectArray[i]->Update(dt);
    }
}

void State::RenderArray(){
    for (int i = 0; i < (int)objectArray.size(); i++){
        objectArray[i]->Render();
    }
}
