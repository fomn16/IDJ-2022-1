#include "Rect.hpp"

Rect::Rect(float _x, float _y, float _w, float _h){
    x = _x;
    y = _y;
    w = _w;
    h = _h;
}

bool Rect::Contains(Vec2 pos){    
    return (    pos.x >= x && 
                pos.x <= x + w &&
                pos.y >= y &&
                pos.y <= y + h
            );
}