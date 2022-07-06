#include "Music.hpp"
#include <iostream>
#include <fstream>

Music::Music(){
    music = nullptr;
}

Music::Music(std::string file){
    Open(file);
}

Music::~Music(){
    Stop(0);
    Mix_FreeMusic(music);
}

void Music::Play(int times){
    if(music != nullptr){
        if(Mix_PlayMusic(music, times)){
            
            std::ofstream fw("logs.txt", std::ofstream::out);
            fw<<"Erro ao tocar musica: "<<SDL_GetError();
            fw.close();
            exit(1);
        }
    }
}

void Music::Stop(int msToStop){
    if(!Mix_FadeOutMusic(msToStop)){
        std::ofstream fw("logs.txt", std::ofstream::out);
        fw<<"Erro ao parar musica: "<<SDL_GetError();
        fw.close();
        exit(1);
    }
}

void Music::Open(std::string file){
    music = Mix_LoadMUS(file.c_str());
    if(music == nullptr){
        std::ofstream fw("logs.txt", std::ofstream::out);
        fw<<"Erro ao carregar musica: "<<SDL_GetError();
        fw.close();
        exit(1);
    }
}

bool Music::IsOpen(){
    return music != nullptr;
}
