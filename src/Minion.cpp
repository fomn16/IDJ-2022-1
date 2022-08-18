#include "Minion.hpp"
#include "Sprite.hpp"

Minion::Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg) 
: Component(associated), alienCenter(alienCenter), arc(arcOffsetDeg){
    Sprite* sprite = new Sprite(associated, "assets/img/minion.png");
    associated.AddComponent(sprite);
}

void Minion::Update(float dt){
    if(alienCenter.lock().get() == nullptr){
        associated.RequestDelete();
        return;
    }
    arc += ANG_SPEED*dt;
    Vec2 pos(INIT_DIST,0);
    pos = pos.GetRotated(arc);
    associated.box.x = (alienCenter.lock()->box.x + alienCenter.lock()->box.w/2) + pos.x - associated.box.w/2;
    associated.box.y = (alienCenter.lock()->box.y + alienCenter.lock()->box.h/2) + pos.y - associated.box.h/2;
}

void Minion::Render(){

}

bool Minion::Is(std::string type){
    return !type.compare("Minion");
}

void Minion::Shoot(Vec2 target){

}

void Minion::Start(){}