#include "PenguinBody.hpp"
#include "PenguinCannon.hpp"
#include "Sprite.hpp"
#include "Game.hpp"

PenguinBody* PenguinBody::player = nullptr;

PenguinBody::PenguinBody(GameObject& associated) :  Component(associated), 
                                                    speed(0,0),
                                                    linearSpeed(0),
                                                    angle(0),
                                                    hp(50){
    player = this;
    
    new Sprite(associated, "assets/img/penguin.png");
    
    inputManager = &InputManager::GetInstance();
    associated.camera->Follow(&associated);
}

PenguinBody::~PenguinBody(){
    player = nullptr;
    associated.camera->Unfollow();
}

void PenguinBody::Start(){
    GameObject* cannonGo = new GameObject(associated.camera);
    new PenguinCannon(*cannonGo, Game::GetInstance().GetState().GetObjectPtr(&associated));
    Game::GetInstance().GetState().AddObject(cannonGo);
    pcannon = Game::GetInstance().GetState().GetObjectPtr(cannonGo);
}

void PenguinBody::Update(float dt){
    if(hp <= 0){
        if(pcannon.lock().get() != nullptr)
            pcannon.lock()->RequestDelete();
        associated.RequestDelete();
        return;
    }

    if(inputManager->IsKeyDown(W_KEY)){
        linearSpeed += PENGUIN_ACC;
        linearSpeed = linearSpeed > PENGUIN_MAX_SP ? PENGUIN_MAX_SP : linearSpeed;
    }
    if(inputManager->IsKeyDown(S_KEY)){
        linearSpeed -= PENGUIN_ACC;
        linearSpeed = linearSpeed < -PENGUIN_MAX_SP ? -PENGUIN_MAX_SP : linearSpeed;
    }
    if(inputManager->IsKeyDown(A_KEY))
        angle += PENGUIN_ANG_ACC;
    if(inputManager->IsKeyDown(D_KEY))
        angle -= PENGUIN_ANG_ACC;

    speed = Vec2(linearSpeed, 0).GetRotated(angle);
    associated.box.x += speed.x;
    associated.box.y += speed.y;
    
    associated.angleDeg = angle*180/M_PI;
}

void PenguinBody::Render(){}

bool PenguinBody::Is(std::string type){
    return !type.compare("PenguinBody");
}
