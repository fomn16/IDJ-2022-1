#ifndef __PENGUIN_BODY_H__
#define __PENGUIN_BODY_H__

#include <string>

#include "Component.hpp"
#include "GameObject.hpp"
#include "InputManager.hpp"

#define PENGUIN_ACC 1
#define PENGUIN_ANG_ACC 0.1
#define PENGUIN_MAX_SP 25

class PenguinBody : public Component{
    public:
        PenguinBody(GameObject& associated);
        ~PenguinBody();

        void Start();
        void Update(float dt);
        void Render();
        bool Is(std::string type);

        static PenguinBody* player;

    private:
        std::weak_ptr<GameObject> pcannon;
        Vec2 speed;
        float linearSpeed;
        float angle;
        int hp;
        InputManager* inputManager;
};

#endif