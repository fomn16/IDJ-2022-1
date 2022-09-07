#ifndef __VEC2_H__
#define __VEC2_H__

class Vec2{
    public:
        Vec2(float _x = 0, float _y = 0);
        Vec2 GetRotated(float angle);
        Vec2 operator+(const Vec2& v) const;
        Vec2 operator-(const Vec2& v) const;
        Vec2 operator*(const float f) const;
        Vec2 operator/(const float f) const;
        Vec2 operator*(const Vec2& v) const;
        float x, y;

        //retorna vec2 com a mesma direção e sentido e módulo max, caso seu módulo seja
        //maior que max. se não, retorna vetor nulo
        Vec2 getClampedOrZero(float max);

        //magnitude do vetor
        float Mag();
        
        bool isZero();
};

#endif