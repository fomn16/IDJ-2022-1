#include "Resources.hpp"
#include "Game.hpp"
#include <fstream>

std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;

//Lógica seguida em Clear: https://en.cppreference.com/w/cpp/container/unordered_map/erase

SDL_Texture* Resources::GetImage(std::string file){
    auto lookup = Resources::imageTable.find(file);
    if (lookup != Resources::imageTable.end())
        return lookup->second;

    SDL_Texture* texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());

    if (texture == nullptr){
        std::ofstream fw("logs.txt", std::ofstream::out);
        fw<<"Erro ao carregar sprite: "<<SDL_GetError();
        fw.close();
        exit(1);
    }

    Resources::imageTable.insert({file, texture});   

    return texture; 
}

void Resources::ClearImages(){
    for(auto it = Resources::imageTable.begin(); it != Resources::imageTable.end(); it++){
        SDL_DestroyTexture(it->second);
        it = Resources::imageTable.erase(it);
    }
}

Mix_Music* Resources::GetMusic(std::string file){
    auto lookup = Resources::musicTable.find(file);
    if (lookup != Resources::musicTable.end())
        return lookup->second;

    Mix_Music* music = Mix_LoadMUS(file.c_str());

    if(music == nullptr){
        std::ofstream fw("logs.txt", std::ofstream::out);
        fw<<"Erro ao carregar musica: "<<SDL_GetError();
        fw.close();
        exit(1);
    }

    Resources::musicTable.insert({file, music});   

    return music;
}


void Resources::ClearMusics(){
    for(auto it = Resources::musicTable.begin(); it != Resources::musicTable.end(); it++){
        Mix_FreeMusic(it->second);
        it = Resources::musicTable.erase(it);
    }
}

Mix_Chunk* Resources::GetSound(std::string file){
    auto lookup = Resources::soundTable.find(file);
    if (lookup != Resources::soundTable.end())
        return lookup->second;

    Mix_Chunk* chunk = Mix_LoadWAV(file.c_str());

    if(chunk == nullptr){
        std::ofstream fw("logs.txt", std::ofstream::out);
        fw<<"Erro ao carregar som: "<<SDL_GetError();
        fw.close();
        exit(1);
    }

    Resources::soundTable.insert({file, chunk});   

    return chunk;
}
        
void Resources::ClearSounds(){
    for(auto it = Resources::soundTable.begin(); it != Resources::soundTable.end(); it++){
        Mix_FreeChunk(it->second);
        it = Resources::soundTable.erase(it);
    }
}

