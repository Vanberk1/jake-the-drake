#include "rendereable.h"
#include <iostream>

void Rendereable::LoadTexture(std::string name, int width, int height, int scale) {
    m_Texture = textureManager.GetTexture(name);
    m_Scale = scale;
    
    m_Source.x = 0;
    m_Source.y = 0;
    m_Source.w = width;
    m_Source.h = height;

    m_Body.x = m_Position.x;
    m_Body.y = m_Position.y;
    m_Body.w = width * scale;
    m_Body.h = height * scale;
}

void Rendereable::Render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, m_Texture, &m_Source, &m_Body);
}

glm::vec2 Rendereable::GetPosition() const {
    return m_Position;
}

glm::vec2 Rendereable::GetVelocity() const {
    return m_Velocity;
}

int Rendereable::GetWidth() const {
    return m_Body.w;
}

int Rendereable::GetHeight() const {
    return m_Body.h;
}

int Rendereable::GetScale() const {
    return m_Scale;
}

void Rendereable::SetPosition(int posX, int posY) {
    m_Position.x = posX;
    m_Position.y = posY;
}

void Rendereable::SetVelocity(int velX, int velY) {
    m_Velocity.x = velX;
    m_Velocity.y = velY;
}

void Rendereable::SetScale(int scale) {
    m_Scale = scale;
}