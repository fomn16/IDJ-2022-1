#ifndef __VEC2_H__
#define __VEC2_H__

class Vec2{
    public:
        Vec2(float _x = 0, float _y = 0);
        Vec2 GetRotated(float angle);
        Vec2 operator+(const Vec2& v) const;
        float x, y;
};

#endif