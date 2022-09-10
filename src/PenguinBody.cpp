#include "PenguinBody.hpp"
#include "PenguinCannon.hpp"
#include "Sprite.hpp"
#include "Game.hpp"
#include "Collider.hpp"
#include "Bullet.hpp"
#include "Sound.hpp"

PenguinBody* PenguinBody::player = nullptr;

PenguinBody::PenguinBody(GameObject& associated) :  Component(associated), 
                                                    speed(0,0),
                                                    linearSpeed(0),
                                                    angle(0),
                                                    hp(PBODY_HP){
    player = this;
    
    new Sprite(associated, "assets/img/penguin.png");
    
    inputManager = &InputManager::GetInstance();
    associated.camera->Follow(&associated);
    new Collider(associated, Vec2(0.5,0.5));
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
    //morte
    if(hp <= 0){
        GameObject* explosion = new GameObject(associated.camera);
        new Sprite(*explosion, "assets/img/penguindeath.png", 5, 0.05, 0.8);
        Sound* s = new Sound(*explosion, "assets/audio/boom.wav");
        s->Play();
        explosion->box.SetCenter(associated.box.GetCenter());
        Game::GetInstance().GetState().AddObject(explosion);

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
    
    associated.angleDeg = angle;
}

bool PenguinBody::Is(std::string type){
    return !type.compare("PenguinBody");
}

void PenguinBody::NotifyCollision(GameObject& other){
    Bullet* b = (Bullet*)other.GetComponent("Bullet");
    if( b != nullptr && b->targetsPlayer)
        hp -= b->GetDamage();
}

void PenguinBody::ApplyDamage(int damage){
    hp -= damage;
}

Vec2 PenguinBody::AssociatedPosition(){
    return associated.box.GetCenter();
}