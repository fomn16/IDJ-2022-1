#ifndef __BULLET_H__
#define __BULLET_H__

#include "Component.hpp"
#include "GameObject.hpp"
#include "Vec2.hpp"

class Bullet : public Component{
    public:
        Bullet(GameObject& associated, bool targetsPlayer, float angle, float speed, int damage, float maxDistance, std::string sprite, int frameCount = 1);
        void Update(float dt);
        bool Is(std::string type);
        int GetDamage();
        void NotifyCollision(GameObject& other);
        bool targetsPlayer;
    private:
        Vec2 speed;
        float speedMag;
        int damage;
        float distanceLeft;
};

#endif