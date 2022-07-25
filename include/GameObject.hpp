#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include "Component.hpp"
#include "Rect.hpp"
#include "Camera.hpp"

#include <string>
#include <vector>
#include <memory>

class Component;
class Camera;

class GameObject{
    public:
        GameObject();
        GameObject(Camera* Camera);
        ~GameObject();

        void Update(float dt);
        void Render();
        bool IsDead();
        void RequestDelete();
        void AddComponent(Component* cpt);
        void RemoveComponent(Component* cpt);
        Component* GetComponent(std::string type);
        Camera* camera = nullptr;

        Rect box;

    private:
        std::vector<std::unique_ptr<Component>> components;
        bool isDead;
};

#endif