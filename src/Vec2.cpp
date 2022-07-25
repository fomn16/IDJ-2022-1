#include "Vec2.hpp"
#include <math.h>

Vec2::Vec2(float _x, float _y){
    x = _x;
    y = _y;
}

Vec2 Vec2::GetRotated(float angle){
    float nx, ny;
    nx = x * cos(angle) - y * sin(angle);
    ny = y * cos(angle) + x * sin(angle);
    return Vec2(nx, ny);
}

Vec2 Vec2::operator+(const Vec2& v) const{
    return Vec2(x + v.x, y + v.y);
}