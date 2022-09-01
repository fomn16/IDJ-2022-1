#include "Bullet.hpp"
#include "Sprite.hpp"
#include <stdio.h>
#include<math.h>

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite)
: Component(associated), speed(speed, 0), speedMag(speed), damage(damage), distanceLeft(maxDistance)
{
    Sprite* bulletSprite = new Sprite(associated, sprite);
    this->speed = this->speed.GetRotated(angle);
    associated.angleDeg = angle*180/M_PI;
}

void Bullet::Update(float dt){
    distanceLeft -= speedMag*dt;
    if(distanceLeft <=0){
        associated.RequestDelete();
        return;
    }
    associated.box.x += speed.x * dt;
    associated.box.y += speed.y * dt;
}

void Bullet::Render(){}

bool Bullet::Is(std::string type){
    return !type.compare("Alien");
}

int Bullet::GetDamage(){
    return damage;
}

void Bullet::Start(){}