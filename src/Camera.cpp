#include "Camera.hpp"
#include "Game.hpp"

Camera::Camera() : pos(){
    inputManager = &InputManager::GetInstance();
}

void Camera::Follow(GameObject* newFocus){
    focus = newFocus;
}

void Camera::Unfollow(){
    focus = nullptr;
}

void Camera::Update(float dt){
    if(focus != nullptr){
        pos.x = focus->box.x + focus->box.w/2;
        pos.y = focus->box.y + focus->box.h/2;
    }
    else{
        if(inputManager->IsKeyDown(LEFT_ARROW_KEY))
            pos.x -= CAMERA_SPEED*Game::GetInstance().GetdeltaTime();
        if(inputManager->IsKeyDown(RIGHT_ARROW_KEY))
            pos.x += CAMERA_SPEED*Game::GetInstance().GetdeltaTime();
        if(inputManager->IsKeyDown(UP_ARROW_KEY))
            pos.y -= CAMERA_SPEED*Game::GetInstance().GetdeltaTime();
        if(inputManager->IsKeyDown(DOWN_ARROW_KEY))
            pos.y += CAMERA_SPEED*Game::GetInstance().GetdeltaTime();
    }
}
