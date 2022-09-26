#ifndef __RESOURCES_H__
#define __RESOURCES_H__

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"

#include <string>
#include <unordered_map>
#include<memory>

class Resources{
    public:
        static std::shared_ptr<SDL_Texture> GetImage(std::string file);
        static void ClearImages();

        static Mix_Music* GetMusic(std::string file);
        static void ClearMusics();

        static Mix_Chunk* GetSound(std::string file);
        static void ClearSounds();

        static TTF_Font* GetFont(std::string file, int fontSize);
        static void ClearFonts();
    private:
        static std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> imageTable;
        static std::unordered_map<std::string, Mix_Music*> musicTable;
        static std::unordered_map<std::string, Mix_Chunk*> soundTable;
        static std::unordered_map<std::string, TTF_Font*> fontTable;
};

#endif