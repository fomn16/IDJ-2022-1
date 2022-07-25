#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "GameObject.hpp"
#include "Vec2.hpp"
#include "InputManager.hpp"

#define CAMERA_SPEED 500
class GameObject;

class Camera{
    public:
        void Follow(GameObject* newFocus);
        void Unfollow();
        void Update(float dt);

        Vec2 pos;
        Vec2 speed;

        Camera();
    private:
        GameObject * focus = nullptr;
        InputManager * inputManager;
};

#endif