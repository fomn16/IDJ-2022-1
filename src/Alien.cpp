#include "Alien.hpp"
#include "Sprite.hpp"
#include "Minion.hpp"
#include "Game.hpp"
#include <math.h>
#include <stdlib.h>

Alien::Alien(GameObject& associated, int nMinions) : Component(associated), hp(30), nMinions(nMinions){
    inputManager = &InputManager::GetInstance();
    new Sprite(associated, "assets/img/alien.png");
}

Alien::~Alien(){
    minionArray.clear();
}

void Alien::Start(){
    std::weak_ptr<GameObject> weak = Game::GetInstance().GetState().GetObjectPtr(&associated);
    float arcOffset = (2 * M_PI)/nMinions;
    for (int i = 0; i < nMinions; i++){
        GameObject* mO = new GameObject(associated.camera);
        new Minion(*mO, weak, i*arcOffset);
        minionArray.push_back(Game::GetInstance().GetState().AddObject(mO));
    }
}

void Alien::Update(float dt){
    //verificando se houve ação
    associated.angleDeg -= 0.1;
    bool pressed = false, shoot = false, move = false;
    if(inputManager->MousePress(LEFT_MOUSE_BUTTON)){
        pressed = true;
        shoot = true;
    }
    if(inputManager->MousePress(RIGHT_MOUSE_BUTTON)){
        pressed = true;
        move = true;
    }

    //efileirando a ação na posição correta
    if(pressed){
        float x = (float)inputManager->GetMouseX();
        float y = (float)inputManager->GetMouseY();
        
        if(associated.camera != nullptr){
            x += associated.camera->pos.x;
            y += associated.camera->pos.y;
        }

        if(shoot)
            taskQueue.emplace(Action(SHOOT, x, y));
        if(move)
            taskQueue.emplace(Action(MOVE, x, y));
    }

    //executando ações pendentes
    if(!taskQueue.empty()){
        Action action = taskQueue.front();
        switch (action.type)
        {
            case MOVE:
            {
                Vec2 dir = (action.pos - this->associated.box.GetCenter()).getClampedOrZero(ALIEN_SPEED);
                if(dir.isZero()){
                    associated.box.SetCenter(action.pos);
                    taskQueue.pop();
                }
                else{
                    associated.box.x += dir.x;
                    associated.box.y += dir.y;
                }
                break;
            }
            case SHOOT:
            {
                taskQueue.pop();

                int minion = 0;
                float dist = 0, t_dist = 0;
                for(int i = 0; i < nMinions; i++){
                    GameObject* temp_minion = minionArray[i].lock().get();
                    t_dist = (temp_minion->box.GetCenter() - action.pos).Mag();
                    if(i == 0 || dist > t_dist){
                        dist = t_dist;
                        minion = i;
                    }
                }

                std::shared_ptr<GameObject> temp_minion = minionArray[minion].lock();
                Minion* realPtrMinion = (Minion *)temp_minion->GetComponent("Minion");

                realPtrMinion->Shoot(action.pos);
                break;
            }
        }
    }

    if(hp <= 0){
        associated.RequestDelete();
    }
}

void Alien::Render(){

}

bool Alien::Is(std::string type){
    return !type.compare("Alien");
}

Alien::Action::Action(ActionType type, float x, float y):type(type){
    pos = Vec2(x,y);
}