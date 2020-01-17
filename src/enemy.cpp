#include "enemy.h"
#include <iostream>

Enemy::Enemy() {
    SetPosition(0, 0);
    SetVelocity(0, 0);
}

Enemy::Enemy(int posX, int posY, int velX, int velY) {
    SetPosition(posX, posY);
    SetVelocity(velX, velY);
}

Collider Enemy::GetCollider() {
    return m_Collider;
}

void Enemy::Init() {
    m_Collider.Init(m_Body, ENEMY);
}

void Enemy::Update(float deltaTime) {
    m_Position.x += m_Velocity.x * deltaTime;
    m_Position.y += m_Velocity.y * deltaTime;
    m_Body.x = m_Position.x;
    m_Body.y = m_Position.y;

    m_Collider.Update(m_Body);
}

void Enemy::Render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &m_Collider.GetCollider());
    SDL_RenderCopy(renderer, m_Texture, &m_Source, &m_Body);
}

 