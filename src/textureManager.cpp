#include "textureManager.h"

void TextureManager::Init(SDL_Renderer* renderer) {
    m_Renderer = renderer;
}

void TextureManager::AddTexture(std::string name, const char* filepath) {
    SDL_Surface* surface = IMG_Load(filepath);
    SDL_Texture* newTexture = SDL_CreateTextureFromSurface(m_Renderer, surface);
    m_Textures[name] = newTexture;
    SDL_FreeSurface(surface);
}

SDL_Texture* TextureManager::GetTexture(std::string name) {
    if(m_Textures[name]) return m_Textures[name];
    return nullptr;
}