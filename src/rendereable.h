#pragma once

#include "gameObject.h"
#include "textureManager.h"

extern TextureManager textureManager;

class Rendereable : public GameObject {
protected:
    glm::vec2 m_Position;
    glm::vec2 m_Velocity;
    SDL_Texture* m_Texture;
    SDL_Rect m_Source;
    SDL_Rect m_Body;
    int m_Scale;

public:
    void LoadTexture(std::string name, int width, int height, int scale);
    void Render(SDL_Renderer* renderer);
    
    glm::vec2 GetPosition() const;
    glm::vec2 GetVelocity() const;
    int GetWidth() const;
    int GetHeight() const;
    int GetScale() const;
    void SetPosition(int posX, int posY);
    void SetVelocity(int velX, int velY);
    void SetScale(int scale);
};