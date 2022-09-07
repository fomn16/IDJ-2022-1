#include "Minion.hpp"
#include "Sprite.hpp"
#include "Bullet.hpp"
#include "Game.hpp"

Minion::Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg) 
: Component(associated), alienCenter(alienCenter), arc(arcOffsetDeg){
    Sprite* sprite = new Sprite(associated, "assets/img/minion.png");
    float scale = 1 + ((float)(std::rand() % 100))/200.;
    sprite->SetScaleX(scale, scale);
    associated.angleDeg = arcOffsetDeg;
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
    associated.angleDeg = arc*180/M_PI;
}

void Minion::Render(){

}

bool Minion::Is(std::string type){
    return !type.compare("Minion");
}

#include <fstream>
void Minion::Shoot(Vec2 target){
    Vec2 d = target - associated.box.GetCenter();
    float a = atan2(d.y, d.x);

    GameObject* bulletGo = new GameObject(associated.camera);
    bulletGo->box.x = associated.box.x; 
    bulletGo->box.y = associated.box.y; 
    bulletGo->box.w = associated.box.w; 
    bulletGo->box.h = associated.box.h;
    new Bullet(*bulletGo, a, 500, 2, 500, "assets/img/minionbullet2.png", 3);
    
    Game::GetInstance().GetState().AddObject(bulletGo);
}

void Minion::Start(){}