#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include "Component.hpp"
#include "Rect.hpp"

#include <string>
#include <vector>

class Component;

class GameObject{
    public:
        GameObject();
        ~GameObject();

        void Update(float dt);
        void Render();
        bool IsDead();
        void RequestDelete();
        void AddComponent(Component* cpt);
        void RemoveComponent(Component* cpt);
        Component* GetComponent(std::string type);

        Rect box;

    private:
        std::vector<Component*> components;
        bool isDead;
};

#endif