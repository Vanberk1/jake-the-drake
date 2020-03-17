#include "healthBar.h"

HealthBar::HealthBar() {

}

void HealthBar::UpdateHealth(int value) {
    m_ActualHealth += value;
    if(m_ActualHealth < 0) {
        m_ActualHealth = 0;
    }
    if(m_ActualHealth > m_MaxHealth) {
        m_ActualHealth = m_MaxHealth;
    }
}

void HealthBar::SetHealth(int max) {
    m_ActualHealth = max;
    m_MaxHealth = max;
}

int HealthBar::GetActualHealth() const {
    return m_ActualHealth;
}

int HealthBar::GetMaxHealth() const {
    return m_MaxHealth;
}

void HealthBar::Init() {
    m_Red = textureManager.GetTexture("health-red");
    m_Grey = textureManager.GetTexture("health-grey");
    m_Heart = textureManager.GetTexture("heart");
    m_Energy = textureManager.GetTexture("energy");
    
    m_Scale = 2;

    m_Position.x = 35 * m_Scale;
    m_Position.y = 23;
    m_Position.w = 8 * m_Scale;
    m_Position.h = 16 * m_Scale;
}

void HealthBar::Update(float deltaTime) {

}

void HealthBar::Render(SDL_Renderer* renderer) {
    SDL_Rect pos; 
    pos.x = m_Position.x;
    pos.y = m_Position.y;
    pos.w = m_Position.w;
    pos.h = m_Position.h;

    for(int i = 0; i < m_ActualHealth; ++i) {
        pos.x = m_Position.x + i * m_Position.w;
        SDL_RenderCopy(renderer, m_Red, NULL, &pos);
    }
    for(int i = m_ActualHealth; i < m_MaxHealth; ++i) {
        pos.x = m_Position.x + i * m_Position.w;
        SDL_RenderCopy(renderer, m_Grey, NULL, &pos);
    }
    pos.x = m_Position.x - 6 * m_Scale;
    pos.y = m_Position.y + m_Position.h;
    pos.w = 54 * m_Scale;
    pos.h = 5 * m_Scale;
    SDL_RenderCopy(renderer, m_Energy, NULL, &pos);

    pos.x = m_Position.x - 26 * m_Scale;
    pos.y = m_Position.y - 7 * m_Scale;
    pos.w = 32 * m_Scale;
    pos.h = 32 * m_Scale;
    SDL_RenderCopy(renderer, m_Heart, NULL, &pos);
}