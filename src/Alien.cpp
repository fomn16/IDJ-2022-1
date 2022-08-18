#include "Alien.hpp"
#include "Sprite.hpp"
#include "Minion.hpp"
#include "Game.hpp"
#include <math.h>

Alien::Alien(GameObject& associated, int nMinions) : Component(associated), hp(30), nMinions(nMinions){
    inputManager = &InputManager::GetInstance();
    Sprite* sprite = new Sprite(associated, "assets/img/alien.png");
    associated.AddComponent(sprite);
}

Alien::~Alien(){
    minionArray.clear();
}

void Alien::Start(){
    std::weak_ptr<GameObject> weak = Game::GetInstance().GetState().GetObjectPtr(&associated);
    float arcOffset = (2 * M_PI)/nMinions;
    for (int i = 0; i < nMinions; i++){
        GameObject* mO = new GameObject(associated.camera);
        Minion* m = new Minion(*mO, weak, i*arcOffset);
        mO->AddComponent(m);
        minionArray.push_back(Game::GetInstance().GetState().AddObject(mO));
    }
}

void Alien::Update(float dt){
    //verificando se houve ação
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
        float x = (float)inputManager->GetMouseX() - associated.box.w/2;
        float y = (float)inputManager->GetMouseY() - associated.box.h/2;
        
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
        Action front = taskQueue.front();
        switch (front.type)
        {
            case MOVE:
            {
                Vec2 dir = (front.pos - Vec2(this->associated.box.x, this->associated.box.y)).getClampedOrZero(ALIEN_SPEED);
                if(dir.isZero()){
                    associated.box.x = front.pos.x;
                    associated.box.y = front.pos.y;
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
                //depois implementar tiro
                taskQueue.pop();
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