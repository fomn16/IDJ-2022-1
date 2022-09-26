#include "Sprite.hpp"
#include "Game.hpp"
#include <iostream>
#include <fstream>
#include "Resources.hpp"

Sprite::Sprite(GameObject& associated) : Component::Component(associated){
    texture = nullptr;
    scale.x = 1;
    scale.y = 1;
    timeElapsed = 0;
    currentFrame = 0;
}

Sprite::Sprite(GameObject& associated, std::string file, 
        int frameCount, float frameTime, float secondsToSelfDestruct) : Sprite::Sprite(associated){
    this->frameCount = frameCount;
    this->frameTime = frameTime;
    this->secondsToSelfDestruct = secondsToSelfDestruct;

    Open(file);
}

Sprite::~Sprite(){
    texture = nullptr;
}

void Sprite::Open(std::string file){
    texture = Resources::GetImage(file);
    if (SDL_QueryTexture(texture.get(), nullptr, nullptr, &(width), &(height))){
        std::ofstream fw("logs.txt", std::ofstream::out);
        fw<<"Erro ao carregar sprite: "<<SDL_GetError();
        fw.close();
        exit(1);
    }
    
    SetClip(0,0,width/frameCount, height);
}

void Sprite::SetClipByIndex (int id){
    this->SetClip(id*clipRect.w,0,clipRect.w, clipRect.h);
}

void Sprite::SetClip (int x, int y, int w, int h){
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;

    associated.box.SetDims(Vec2(w,h)*scale, associated.camera != nullptr);
}

void Sprite::Render (){
    Render(associated.box.x, associated.box.y);
}

void Sprite::Render (int x, int y){
    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = associated.box.w;
    dstRect.h = associated.box.h;

    if(associated.camera != nullptr){
        dstRect.x -= associated.camera->pos.x;
        dstRect.y -= associated.camera->pos.y;
    }

    if(SDL_RenderCopyEx(
                    Game::GetInstance().GetRenderer(),
                    texture.get(),
                    &(clipRect),
                    &dstRect,
                    associated.angleDeg*180/M_PI,
                    nullptr,
                    SDL_FLIP_NONE)){
        std::ofstream fw("logs.txt", std::ofstream::out);
        fw<<"Erro ao renderizar sprite: "<<SDL_GetError();
        fw.close();
        exit(1);
    }
}

int Sprite::GetWidth(){
    return width*scale.x/frameCount;
}

int Sprite::GetHeight(){
    return height*scale.y;
}

bool Sprite::IsOpen(){
    return texture != nullptr;
}

void Sprite::Update(float dt){
    selfDestructCount.Update(dt);
    if(secondsToSelfDestruct != 0 && selfDestructCount.Get() >= secondsToSelfDestruct){
        associated.RequestDelete();
        return;
    }
    if (frameCount == 1)    //evitando computações desnecessárias
        return;
    timeElapsed += dt;
    if(timeElapsed > frameTime){
        timeElapsed = 0;
        currentFrame++;
        currentFrame %= frameCount;
        SetClipByIndex(currentFrame);
    }
}

bool Sprite::Is(std::string type){
    return !type.compare("Sprite");
}

void Sprite::SetScaleX(float scaleX, float scaleY){
        scale.x = scaleX ? scaleX : scale.x;
        scale.y = scaleY ? scaleY : scale.y;

        associated.box.SetDims(Vec2(width*scale.x/frameCount, height*scale.y));
}

Vec2 Sprite::GetScale(){
    return scale;
}

void Sprite::SetFrame(int frame){
    currentFrame = frame%frameCount;    //tratamento se frame for maior que o número disponível
    SetClipByIndex(frame);
}

void Sprite::SetFrameCount(int frameCount){
    this->frameCount = frameCount;
    SetClip(0,0,width/frameCount, height);
}

void Sprite::SetFrameTime(float frameTime){
    this->frameTime = frameTime;
}
