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

void Rect::SetCenter(Vec2 center){
    x = center.x - w/2;
    y = center.y - h/2;
}

void Rect::SetDims(Vec2 dims, bool keepCenter){
    if(dims.x){
        if (keepCenter)
            x += (w - dims.x)/2;
        w = dims.x;
    }
    if(dims.y){
        if (keepCenter)
           y += (h - dims.y)/2;
        h = dims.y;
    }
}

Vec2 Rect::GetCenter(){
    return Vec2(x + w/2, y + h/2);
}
