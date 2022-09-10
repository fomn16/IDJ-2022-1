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

Vec2 Vec2::operator-(const Vec2& v) const{
    return Vec2(x - v.x, y - v.y);
}

Vec2 Vec2::operator*(const float f) const{
    return Vec2(x*f, y*f);
}

Vec2 Vec2::operator*(const Vec2& v) const{
    return Vec2(x*v.x, y*v.y);
}

Vec2 Vec2::operator/(const float f) const{
    return Vec2(x/f, y/f);
}

float Vec2::Mag(){
    return sqrt(x*x + y*y);
}

Vec2 Vec2::getClampedOrZero(float max){
    float mag = this->Mag();
    if(mag > max)
        return this->operator/(mag).operator*(max);
    return Vec2();  
}

bool Vec2::isZero(){
    return x == 0 && y == 0;
}