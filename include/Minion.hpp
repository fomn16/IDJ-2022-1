#ifndef __MINION_H__
#define __MINION_H__

#include "Component.hpp"
#include "GameObject.hpp"
#include <math.h>
#include <string>

#define ANG_SPEED M_PI/3
#define INIT_DIST 200

class Minion : public Component{
    public:
        Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0);
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        void Shoot(Vec2 target);
        void Start();

    private:
        std::weak_ptr<GameObject> alienCenter;
        float arc;
}; 

#endif