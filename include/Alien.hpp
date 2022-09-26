#ifndef __ALIEN_H__
#define __ALIEN_H__

#include "GameObject.hpp"
#include "Vec2.hpp"
#include "Timer.hpp"

#include <string>
#include <queue>
#include <vector>

#define ALIEN_SPEED 5
#define ALIEN_REST_TIME 0.2
#define ALIEN_HP 24

class Alien : public Component
{
    public:
        Alien(GameObject& associated, int nMinions, float timeOffset);
        ~Alien();
        void Start();
        void Update(float dt);
        bool Is(std::string type);
        void NotifyCollision(GameObject& other);

        static int alienCount;
    private:
        
        Timer restTimer;
        Vec2 destination;
        enum AlienState{MOVING, RESTING};
        AlienState state;

        Vec2 speed;
        int hp, nMinions;
        std::vector<std::weak_ptr<GameObject>> minionArray;
        
        float timeOffset;

};

#endif