#include "Alien.hpp"
#include "Sprite.hpp"
#include "Minion.hpp"
#include "Game.hpp"
#include <math.h>
#include <stdlib.h>
#include "Collider.hpp"
#include "Bullet.hpp"
#include "GameObject.hpp"
#include "Sound.hpp"
#include "PenguinBody.hpp"

int Alien::alienCount = 0;

Alien::Alien(GameObject& associated, int nMinions) : Component(associated), state(RESTING), hp(ALIEN_HP), nMinions(nMinions){
    new Sprite(associated, "assets/img/alien.png");
    new Collider(associated, Vec2(0.5,0.5));
    Alien::alienCount++;
}

Alien::~Alien(){
    minionArray.clear();
    Alien::alienCount--;
}

void Alien::Start(){
    std::weak_ptr<GameObject> weak = Game::GetInstance().GetCurrentState().GetObjectPtr(&associated);
    float arcOffset = (2 * M_PI)/nMinions;
    for (int i = 0; i < nMinions; i++){
        GameObject* mO = new GameObject(associated.camera);
        new Minion(*mO, weak, i*arcOffset);
        minionArray.push_back(Game::GetInstance().GetCurrentState().AddObject(mO));
    }
}

void Alien::Update(float dt){
    //morte
    if(hp <= 0){
        GameObject* explosion = new GameObject(associated.camera);
        new Sprite(*explosion, "assets/img/aliendeath.png", 4, 0.1, 0.8);
        Sound* s = new Sound(*explosion, "assets/audio/boom.wav");
        s->Play();
        explosion->box.SetCenter(associated.box.GetCenter());
        Game::GetInstance().GetCurrentState().AddObject(explosion);

        associated.RequestDelete();
    }

    //limpando minionArray
    for (int i = 0; i < (int)minionArray.size(); i++){
        if(minionArray[i].expired() || minionArray[i].lock().get() == nullptr){
            minionArray.erase(minionArray.begin() + i);
        }
    }
    
    associated.angleDeg -= 0.05; //girando alien um pouco

    if(PenguinBody::player == nullptr)
        return;
    restTimer.Update(dt);

    switch (state)
    {
        case RESTING:
            if(restTimer.Get() >= ALIEN_REST_TIME){
                destination = PenguinBody::player->AssociatedPosition();
                state = MOVING;
            }
            break;
        
        case MOVING:
            Vec2 dir = (destination - this->associated.box.GetCenter()).getClampedOrZero(ALIEN_SPEED);
            if(dir.isZero()){
                destination = PenguinBody::player->AssociatedPosition();
                int minion = -1;
                float dist = 0, t_dist = 0;
                for(int i = 0; i < (int)minionArray.size(); i++){
                    GameObject* temp_minion = minionArray[i].lock().get(); 
                    t_dist = (temp_minion->box.GetCenter() - destination).Mag();
                    if(minion == -1 || dist > t_dist){
                        dist = t_dist;
                        minion = i;
                    }
                }

                if(minion != -1){
                    std::shared_ptr<GameObject> temp_minion = minionArray[minion].lock();
                    Minion* realPtrMinion = (Minion *)temp_minion->GetComponent("Minion");
                    realPtrMinion->Shoot(destination);
                }
                restTimer.Restart();
                state = RESTING;
            }
            else{
                associated.box.x += dir.x;
                associated.box.y += dir.y;
            }
            break;
    }
}

bool Alien::Is(std::string type){
    return !type.compare("Alien");
}

void Alien::NotifyCollision(GameObject& other){
    Bullet* b = (Bullet*)other.GetComponent("Bullet");
    if( b != nullptr && !b->targetsPlayer)
        hp -= b->GetDamage();
}