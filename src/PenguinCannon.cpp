#include "PenguinCannon.hpp"
#include "Sprite.hpp"
#include <math.h>
#include "Bullet.hpp"
#include "Game.hpp"
#include "Collider.hpp"
#include "Bullet.hpp"
#include "PenguinBody.hpp"
#include <iostream>

PenguinCannon::PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody) : 
Component(associated),
pbody(penguinBody),
angle(0)
{
    new Sprite(associated, "assets/img/cubngun.png");
    inputManager = &InputManager::GetInstance();
    new Collider(associated, Vec2(0.5,0.5));
}

void PenguinCannon::Update(float dt){
    timer.Update(dt);
    if(pbody.lock().get() == nullptr){
        associated.RequestDelete();
        return;
    }

    associated.box.SetCenter(pbody.lock()->box.GetCenter());
    Vec2 d = inputManager->GetMousePos() - associated.box.GetCenter() + associated.camera->pos;
    angle = atan2(d.y, d.x);
    associated.angleDeg = angle;

    if(inputManager->MousePress(LEFT_MOUSE_BUTTON))
        Shoot();
}

bool PenguinCannon::Is(std::string type){
    return !type.compare("PenguinCannon");
}

void PenguinCannon::Shoot(){
    if(timer.Get()<PCANNON_COOLDOWN)
        return;
    timer.Restart();
    GameObject* bulletGo = new GameObject(associated.camera);
    Vec2 offset = Vec2(associated.box.w/2 + 10, 0).GetRotated(angle);
    bulletGo->box.x = associated.box.x + offset.x;
    bulletGo->box.y = associated.box.y + offset.y;
    bulletGo->box.w = associated.box.w;
    bulletGo->box.h = associated.box.h;


    new Bullet(*bulletGo, false, angle, 500, PCANNON_DAMAGE, 500, "assets/img/penguinbullet.png", 4);
    Game::GetInstance().GetState().AddObject(bulletGo);
}

PenguinCannon::~PenguinCannon(){}

void PenguinCannon::NotifyCollision(GameObject& other){
    Bullet* b = (Bullet*)other.GetComponent("Bullet");
    if( b != nullptr && b->targetsPlayer){
        ((PenguinBody*)pbody.lock()->GetComponent("PenguinBody"))->ApplyDamage(b->GetDamage());
    }
}
