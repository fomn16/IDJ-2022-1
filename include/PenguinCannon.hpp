#ifndef __PENGUIN_CANNON_H__
#define __PENGUIN_CANNON_H__

#include "GameObject.hpp"
#include "Component.hpp"
#include "InputManager.hpp"

class PenguinCannon : public Component{
    public:
        PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody);
        ~PenguinCannon();
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        void Shoot();

        void Start();

    private:
        std::weak_ptr<GameObject> pbody;
        float angle;
        InputManager* inputManager;
};

#endif