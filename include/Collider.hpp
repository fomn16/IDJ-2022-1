#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "Component.hpp"
#include "GameObject.hpp"
#include "Rect.hpp"

class Collider : public Component{
    public:
        Collider (GameObject& associated, Vec2 scale = {1,1}, Vec2 offset = {0,0});
        void Update(float dt);
        bool Is(std::string type);
        void SetScale(Vec2 scale);
        void SetOffset(Vec2 offset);
        void Render();
        
        Rect box;
    private:
        Vec2 offset;
        Vec2 scale;
};

#endif