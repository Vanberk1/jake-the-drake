#include "bullet.h"

Bullet::Bullet() {
    SetPosition(0, 0);
    SetVelocity(0, 0);
    m_Body.w = 4;
    m_Body.h = 4;
}

Bullet::~Bullet() {

}

void Bullet::InitCollider() {
    m_Collider.Init(m_Body, FRIENDLY_PROJECTILE);
}

Collider Bullet::GetCollider() const {
    return m_Collider;
}

void Bullet::Update(float deltaTime) {
    m_Position.x += m_Velocity.x * deltaTime;
    m_Position.y += m_Velocity.y * deltaTime;

    m_Body.x = m_Position.x;
    m_Body.y = m_Position.y;

    m_Collider.Update(m_Body);
}

void Bullet::Render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &m_Collider.GetCollider());
    SDL_RenderCopy(renderer, m_Texture, &m_Source, &m_Body);
}