#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <string>

class TextureManager {
private:
    SDL_Renderer* m_Renderer;
    std::map<std::string, SDL_Texture*> m_Textures;

public:
    void Init(SDL_Renderer* renderer);
    void AddTexture(std::string name, const char* filepath);
    SDL_Texture* GetTexture(std::string name);
};