#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "GameObject.hpp"
#include <string>

class GameObject;

class Component{
    public:
        Component(GameObject& associated);
        virtual ~Component();
        virtual void Update(float dt) = 0;
        virtual void Render() = 0;
        virtual bool Is(std::string type) = 0;
        virtual void Start() = 0;
    protected:
        GameObject& associated;
};

#endif