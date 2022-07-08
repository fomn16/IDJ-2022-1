#include "Sound.hpp"
#include <fstream>

Sound::Sound(GameObject& associated) : Component::Component(associated){
    chunk = nullptr;
}

Sound::Sound(GameObject& associated, std::string file) : Sound::Sound(associated){
    Open(file);
}

Sound::~Sound(){
    if(chunk != nullptr){
        Stop();
        Mix_FreeChunk(chunk);
    }
}

void Sound::Play(int times){
    channel = Mix_PlayChannel(-1, chunk, times - 1);
    if(channel == -1){
         std::ofstream fw("logs.txt", std::ofstream::out);
        fw<<"Erro tocando som: " <<SDL_GetError();
        fw.close();
    }
}

void Sound::Stop(){
    if(chunk != nullptr){
        Mix_HaltChannel(channel);
    }
}

void Sound::Open(std::string file){
    chunk = Mix_LoadWAV(file.c_str());
    if(chunk == nullptr){
        std::ofstream fw("logs.txt", std::ofstream::out);
        fw<<"Erro ao carregar som: "<<SDL_GetError();
        fw.close();
        exit(1);
    }
}

bool Sound::IsOpen(){
    return chunk!=nullptr;
}

void Sound::Update(float dt){

}

void Sound::Render(){

}

bool Sound::Is(std::string type){   
    return !type.compare("Sound");
}