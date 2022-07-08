#include "Sprite.hpp"
#include "Game.hpp"
#include <iostream>
#include <fstream>

Sprite::Sprite(GameObject& associated) : Component::Component(associated){
    texture = nullptr;
}

Sprite::Sprite(GameObject& associated, const char* file) : Sprite::Sprite(associated){
    Open(file);
}

Sprite::~Sprite(){
    if(texture != nullptr)
        SDL_DestroyTexture(texture);
}

void Sprite::Open(const char* file){
    if(texture != nullptr)
        SDL_DestroyTexture(texture);
    texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file);
    if (texture == nullptr){
        std::ofstream fw("logs.txt", std::ofstream::out);
        fw<<"Erro ao carregar sprite: "<<SDL_GetError();
        fw.close();
        exit(1);
    }
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

    associated.box.w = w;
    associated.box.h = h;
}

void Sprite::Render (){
    SDL_Rect dstRect;
    dstRect.x = associated.box.x;
    dstRect.y = associated.box.y;
    dstRect.w = clipRect.w;
    dstRect.h = clipRect.h;

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