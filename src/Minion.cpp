#include "Minion.hpp"
#include "Sprite.hpp"
#include "Bullet.hpp"
#include "Game.hpp"
#include "Collider.hpp"

Minion::Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg) 
: Component(associated), alienCenter(alienCenter), arc(arcOffsetDeg){
    Sprite* sprite = new Sprite(associated, "assets/img/minion.png");
    float scale = 1 + ((float)(std::rand() % 100))/200.;
    sprite->SetScaleX(scale, scale);
    associated.angleDeg = arcOffsetDeg;
    new Collider(associated, Vec2(0.5,0.5));
}

void Minion::Update(float dt){
    if(alienCenter.lock().get() == nullptr){
        associated.RequestDelete();
        return;
    }

    arc += ANG_SPEED*dt;
    Vec2 pos(INIT_DIST,0);
    pos = pos.GetRotated(arc);
    associated.box.SetCenter(alienCenter.lock()->box.GetCenter() + pos);
    associated.angleDeg = arc;
}

bool Minion::Is(std::string type){
    return !type.compare("Minion");
}

void Minion::Shoot(Vec2 target){
    Vec2 d = target - associated.box.GetCenter();
    float a = atan2(d.y, d.x);

    GameObject* bulletGo = new GameObject(associated.camera);
    bulletGo->box.x = associated.box.x; 
    bulletGo->box.y = associated.box.y; 
    bulletGo->box.w = associated.box.w; 
    bulletGo->box.h = associated.box.h;
    new Bullet(*bulletGo, true, a, 500, 2, 2000, "assets/img/minionbullet2.png",  3);
    
    Game::GetInstance().GetCurrentState().AddObject(bulletGo);
}

void Minion::NotifyCollision(GameObject& other){
    Bullet* b = (Bullet*)other.GetComponent("Bullet");
    if(b != nullptr && !b ->targetsPlayer){
        associated.RequestDelete();
    }
}