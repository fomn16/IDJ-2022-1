#include "Bullet.hpp"
#include "Sprite.hpp"
#include <stdio.h>
#include<math.h>
#include "Collider.hpp"

Bullet::Bullet( GameObject& associated, bool targetsPlayer, float angle, float speed,
                int damage, float maxDistance, std::string sprite, int frameCount)
:   Component(associated), targetsPlayer(targetsPlayer), speed(speed, 0), speedMag(speed), 
    damage(damage), distanceLeft(maxDistance)
{
    new Sprite(associated, sprite, frameCount, 0.01);
    this->speed = this->speed.GetRotated(angle);
    associated.angleDeg = angle;
    new Collider(associated);
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

bool Bullet::Is(std::string type){
    return !type.compare("Bullet");
}

int Bullet::GetDamage(){
    return damage;
}

void Bullet::NotifyCollision(GameObject& other){
    if(other.GetComponent("Bullet") == nullptr){
        if((other.GetComponent("PenguinBody") || other.GetComponent("PenguinCannon")) == targetsPlayer)
            associated.RequestDelete();
    }
}