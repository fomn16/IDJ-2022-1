#ifndef __RECT_H__
#define __RECT_H__

#include "Vec2.hpp"

class Rect{
    public:
        Rect(float _x = 0, float _y = 0, float _w = 0, float _h = 0);
        bool Contains(Vec2 pos);
        float x, y, w, h;
        void SetCenter(Vec2 center);
        void SetDims(Vec2 dims, bool keepCenter = true);
        Vec2 GetCenter();
};

#endif