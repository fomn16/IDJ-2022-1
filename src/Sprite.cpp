#include "Sprite.hpp"
#include "Game.hpp"
#include <iostream>
#include <fstream>
#include "Resources.hpp"

Sprite::Sprite(GameObject& associated) : Component::Component(associated){
    texture = nullptr;
}

Sprite::Sprite(GameObject& associated, std::string file) : Sprite::Sprite(associated){
    Open(file);
}

Sprite::~Sprite(){
}

void Sprite::Open(std::string file){
    texture = Resources::GetImage(file);
    
    if (SDL_QueryTexture(texture, nullptr, nullptr, &(width), &(height))){
        std::ofstream fw("logs.txt", std::ofstream::out);
        fw<<"Erro ao carregar sprite: "<<SDL_GetError();
        fw.close();
        exit(1);
    }
    
    SetClip(0,0,width, height);
}

void Sprite::SetClip (int x, int y, int w, int h){
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;

    if(associated.camera != nullptr){
        if(associated.box.w || associated.box.h){
            associated.box.x += associated.box.w/2;
            associated.box.y += associated.box.h/2;
        }
        associated.box.x -= w/2;
        associated.box.y -= h/2;
    }

    associated.box.w = w;
    associated.box.h = h;
}

void Sprite::Render (){
    Render(associated.box.x, associated.box.y);
}

void Sprite::Render (int x, int y){
    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = clipRect.w;
    dstRect.h = clipRect.h;

    if(associated.camera != nullptr){
        dstRect.x -= associated.camera->pos.x;
        dstRect.y -= associated.camera->pos.y;
    }

    if(SDL_RenderCopy(Game::GetInstance().GetRenderer(),
                   texture,
                   &(clipRect),
                   &dstRect)){
        std::ofstream fw("logs.txt", std::ofstream::out);
        fw<<"Erro ao renderizar sprite: "<<SDL_GetError();
        fw.close();
        exit(1);
    }
}

int Sprite::GetWidth(){
    return width;
}

int Sprite::GetHeight(){
    return height;
}

bool Sprite::IsOpen(){
    return texture != nullptr;
}

void Sprite::Update(float dt){

}

bool Sprite::Is(std::string type){
    return !type.compare("Sprite");
}

void Sprite::Start(){}