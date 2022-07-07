#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "GameObject.hpp"
#include <string>
class Component{
    public:
        Component(GameObject& associatd);
        virtual ~Component();
        virtual void Update(float dt);
        virtual void Render();
        virtual bool Is(std::string type);
    protected:
        GameObject& associated;
};

#endif