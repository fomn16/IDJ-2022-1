#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "GameObject.hpp"
#include <string>

class GameObject;

class Component{
    public:
        Component(GameObject& associated);
        virtual ~Component();
        virtual void Update(float dt);
        virtual void Render();
        virtual void Start();
        virtual bool Is(std::string type) = 0;
        virtual void NotifyCollision(GameObject& other);
    protected:
        GameObject& associated;
};

#endif