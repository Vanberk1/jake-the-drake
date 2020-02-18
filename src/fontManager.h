#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <map>
#include <string>
#include <sstream>
#include <iostream>

class FontManager {
private:
    SDL_Renderer* m_Renderer;
    std::map<std::string, TTF_Font*> m_Fonts;
public:
    void Init(SDL_Renderer* renderer);
    void AddFont(std::string name, int size, const char* filepath);
    TTF_Font* GetFont(std::string name, int size);
};