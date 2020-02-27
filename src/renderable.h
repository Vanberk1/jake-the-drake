#pragma once

#include "gameObject.h"
#include "animation.h"
#include "textureManager.h"
#include <iostream>
#include <map>

extern TextureManager textureManager;

class Renderable : public GameObject {
protected:
    glm::vec2 m_Position;
    glm::vec2 m_Velocity;
    SDL_Texture* m_Texture;
    SDL_Rect m_Source;
    SDL_Rect m_Body;
    int m_Scale;
    std::map<std::string, Animation> m_Animations;
    std::string m_ActualAnimation;
    bool m_IsAnimated;

public:
    void LoadTexture(std::string name, int width, int height, int scale, bool isAnimated);
    void AddAnimation(std::string animName, int framesNum, int animationSpeed, int animationCount);
    void SetAnimation(std::string animName);
    void Render(SDL_Renderer* renderer);
    
    glm::vec2 GetPosition() const;
    glm::vec2 GetVelocity() const;
    int GetWidth() const;
    int GetHeight() const;
    int GetScale() const;
    void SetPosition(float posX, float posY);
    void SetVelocity(float velX, float velY);
    void SetScale(int scale);
};