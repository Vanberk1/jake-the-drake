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
    m_Red = textureManager.GetTexture("red-heart");
    m_Grey = textureManager.GetTexture("grey-heart");
    
    m_Position.x = 25;
    m_Position.y = 25;
    m_Position.w = 16 * 2;
    m_Position.h = 16 * 2;
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
        pos.x = 25 + i * 18 * 2;
        SDL_RenderCopy(renderer, m_Red, NULL, &pos);
    }

    for(int i = m_ActualHealth; i < m_MaxHealth; ++i) {
        pos.x = 25 + i * 18 * 2;
        SDL_RenderCopy(renderer, m_Grey, NULL, &pos);
    }
}