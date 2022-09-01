#ifndef __ALIEN_H__
#define __ALIEN_H__

#include "GameObject.hpp"
#include "Vec2.hpp"
#include "InputManager.hpp"

#include <string>
#include <queue>
#include <vector>

#define ALIEN_SPEED 5


enum ActionType{MOVE, SHOOT};

class Alien : public Component
{
    public:
        Alien(GameObject& associated, int nMinions);
        ~Alien();
        void Start();
        void Update(float dt);
        void Render();
        bool Is(std::string type);
    private:
        class Action{
            public:
                Action(ActionType type, float x, float y);
                ActionType type;
                Vec2 pos;
        };

        Vec2 speed;
        int hp, nMinions;
        std::queue<Action> taskQueue;
        std::vector<std::weak_ptr<GameObject>> minionArray;
        InputManager* inputManager;
};

#endif