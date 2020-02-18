#include "fontManager.h"

void FontManager::Init(SDL_Renderer* renderer) {
    m_Renderer = renderer;
}

void FontManager::AddFont(std::string name, int size, const char* filepath) {
    TTF_Font* font = TTF_OpenFont(filepath, size);
    std::stringstream ss;
    ss << name << "-" << size;
    std::string completeName = ss.str();
    m_Fonts[completeName] = font;
}

TTF_Font* FontManager::GetFont(std::string name, int size) {
    std::stringstream ss;
    ss << name << "-" << size;
    std::string completeName = ss.str();
    if(m_Fonts[completeName]) return m_Fonts[completeName];
    return nullptr;
}