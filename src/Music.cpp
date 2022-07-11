#include "Music.hpp"
#include "Resources.hpp"
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
    music = Resources::GetMusic(file);        
}

bool Music::IsOpen(){
    return music != nullptr;
}
