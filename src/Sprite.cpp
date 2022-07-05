#include "Sprite.hpp"
#include "Game.hpp"
#include <iostream>

Sprite::Sprite(){
    texture = nullptr;
}

Sprite::Sprite(const char* file){
    texture = nullptr;
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
        std::cout<<"Erro ao carregar sprite: "<<SDL_GetError();
        exit(1);
    }
    if (SDL_QueryTexture(texture, nullptr, nullptr, &(width), &(height))){
        std::cout<<"Erro ao carregar sprite: "<<SDL_GetError();
        exit(1);
    }
    SetClip(0,0,width, height);
}

void Sprite::SetClip (int x, int y, int w, int h){
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render (int x, int y){
    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = clipRect.w;
    dstRect.h = clipRect.h;

    if(SDL_RenderCopy(Game::GetInstance().GetRenderer(),
                   texture,
                   &(clipRect),
                   &dstRect)){
        std::cout<<"Erro ao renderizar sprite: "<<SDL_GetError();
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