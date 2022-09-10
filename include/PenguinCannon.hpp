#ifndef __PENGUIN_CANNON_H__
#define __PENGUIN_CANNON_H__

#include "GameObject.hpp"
#include "Component.hpp"
#include "InputManager.hpp"
#include "Timer.hpp"

#define PCANNON_COOLDOWN 0.5
#define PCANNON_DAMAGE 4

class PenguinCannon : public Component{
    public:
        PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody);
        ~PenguinCannon();
        void Update(float dt);
        bool Is(std::string type);
        void Shoot();
        void NotifyCollision(GameObject& other);

    private:
        std::weak_ptr<GameObject> pbody;
        float angle;
        InputManager* inputManager;
        Timer timer;
};

#endif