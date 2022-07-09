#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include "Component.hpp"
#include "Rect.hpp"

#include <string>
#include <vector>
#include <memory>

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
        std::vector<std::unique_ptr<Component>> components;
        bool isDead;
};

#endif