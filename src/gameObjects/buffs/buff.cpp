#include "buff.h"

void Buff::Init() {
    m_Collider.Init(m_Body, BUFF);
}

void Buff::Update(float deltaTime) {
    m_Position.x += m_Velocity.x * deltaTime;
    m_Position.y += m_Velocity.y * deltaTime;
    m_Body.x = m_Position.x;
    m_Body.y = m_Position.y;

    m_Collider.Update(m_Body);
}

Collider Buff::GetCollider() const {
    return m_Collider;
}