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
    SDL_RenderCopy(renderer, m_Texture, &m_Source, &m_Body);
}

 