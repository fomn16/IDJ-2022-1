#ifndef __FACE_H__
#define __FACE_H__

#include "Component.hpp"
#include "GameObject.hpp"

#include <string>

class Face : public Component{
    public:
        Face(GameObject& associated);

        void Damage(int damage);

        void Update(float dt);
        void Render();
        bool Is(std::string type);
    private:
        int hitpoints;
};
#endif