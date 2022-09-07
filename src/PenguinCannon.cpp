#include "PenguinCannon.hpp"
#include "Sprite.hpp"
#include <math.h>
#include "Bullet.hpp"
#include "Game.hpp"

PenguinCannon::PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody) : 
Component(associated),
pbody(penguinBody),
angle(0)
{
    new Sprite(associated, "assets/img/cubngun.png");
    inputManager = &InputManager::GetInstance();
}

void PenguinCannon::Update(float dt){
    if(pbody.lock().get()==nullptr)
        associated.RequestDelete();

    associated.box.SetCenter(pbody.lock()->box.GetCenter());
    Vec2 d = inputManager->GetMousePos() - associated.box.GetCenter() + associated.camera->pos;
    angle = atan2(d.y, d.x);
    associated.angleDeg = angle*180/M_PI;

    if(inputManager->MousePress(LEFT_MOUSE_BUTTON))
        Shoot();
}

void PenguinCannon::Render(){}

bool PenguinCannon::Is(std::string type){
    return !type.compare("PenguinCannon");
}

void PenguinCannon::Shoot(){
    GameObject* bulletGo = new GameObject(associated.camera);
    Vec2 offset = Vec2(associated.box.w/2 + 10, 0).GetRotated(angle);
    bulletGo->box.x = associated.box.x + offset.x;
    bulletGo->box.y = associated.box.y + offset.y;
    bulletGo->box.w = associated.box.w;
    bulletGo->box.h = associated.box.h;


    new Bullet(*bulletGo, angle, 500, 2, 500, "assets/img/penguinbullet.png", 4);
    Game::GetInstance().GetState().AddObject(bulletGo);
}

void PenguinCannon::Start(){}
PenguinCannon::~PenguinCannon(){}