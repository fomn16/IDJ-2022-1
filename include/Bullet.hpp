#ifndef __BULLET_H__
#define __BULLET_H__

#include "Component.hpp"
#include "GameObject.hpp"
#include "Vec2.hpp"

class Bullet : public Component{
    public:
        Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite);
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        int GetDamage();
        void Start();
    private:
        Vec2 speed;
        float speedMag;
        int damage;
        float distanceLeft;
};

#endif