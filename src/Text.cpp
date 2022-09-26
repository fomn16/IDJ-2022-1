#include "Text.hpp"
#include "Resources.hpp"
#include "Game.hpp"

#include <iostream>
#include <fstream>

Text::Text(   GameObject& associated, std::string fontFile, int fontSize, TextStyle textStyle, 
        std::string text, SDL_Color color) : Component(associated){
    font = Resources::GetFont(fontFile, fontSize);
    texture = nullptr;
    this->text = text;
    style = textStyle;
    this->fontFile = fontFile;
    this->fontSize = fontSize;
    this->color = color;

    RemakeTexture();
}

Text::~Text(){
    texture = nullptr;
}

void Text::Update(float dt){

}

void Text::Render(){
    SDL_Rect clipRect;
    clipRect.x = 0;
    clipRect.y = 0;
    clipRect.w = associated.box.w;
    clipRect.h = associated.box.h;

    SDL_Rect dstRect;
    dstRect.x = associated.box.x;
    dstRect.y = associated.box.y;
    dstRect.w = associated.box.w;
    dstRect.h = associated.box.h;

    if(associated.camera != nullptr){
        dstRect.x -= associated.camera->pos.x;
        dstRect.y -= associated.camera->pos.y;
    }

    if(SDL_RenderCopyEx(
                    Game::GetInstance().GetRenderer(),
                    texture,
                    &clipRect,
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

bool Text::Is(std::string type){
    return !type.compare("Text");
}

void Text::SetText(std::string text){
    this->text = text;
    RemakeTexture();
}

void Text::SetColor(SDL_Color color){
    this->color = color;
    RemakeTexture();
}

void Text::SetStyle(TextStyle style){
    this->style = style;
    RemakeTexture();
}

void Text::SetFontFile(std::string fontFile){
    this->fontFile = fontFile;
    RemakeTexture();
}

void Text::SetFontSize(int fontSize){
    this->fontSize = fontSize;
    RemakeTexture();
}

void Text::RemakeTexture(){
    texture = nullptr;
    font = Resources::GetFont(fontFile, fontSize);
    SDL_Surface * surface;
    switch (style)
    {
        case SOLID:
            surface = TTF_RenderText_Solid(font, text.c_str(), color);
            break;
        case SHADED:
            surface = TTF_RenderText_Shaded(font, text.c_str(), color, {0, 255, 0, 0});
            break;
        case BLENDED:
            surface = TTF_RenderText_Blended(font, text.c_str(), color);
            break;
    }
    texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(),surface);
    associated.box.SetDims(Vec2(surface->w, surface->h));
    SDL_FreeSurface(surface);
}