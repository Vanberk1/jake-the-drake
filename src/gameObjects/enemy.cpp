#include "enemy.h"
#include <iostream>

int Enemy::GetRewardPoints() const {
    return m_RewardPoints;
}

Collider Enemy::GetCollider() {
    return m_Collider;
}

void Enemy::Init() {
    m_Collider.Init(m_Body, ENEMY);
}

void Enemy::Render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &m_Collider.GetCollider());
    if(m_IsAnimated) {
        m_Source.x = m_Source.w * static_cast<int>((SDL_GetTicks() / m_Animations[m_ActualAnimation].m_AnimationSpeed) % m_Animations[m_ActualAnimation].m_FramesNum);
        m_Source.y = m_Source.h * m_Animations[m_ActualAnimation].m_AnimationCount;
    }
    SDL_RenderCopy(renderer, m_Texture, &m_Source, &m_Body);
}

 