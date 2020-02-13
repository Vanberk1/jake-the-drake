#include "bombEnemy.h"

BombEnemy::BombEnemy(int posX, int posY, int velX, int velY, int points) {
    SetPosition(posX, posY);
    SetVelocity(velX, velY);
    m_CanRush = true;
    m_RewardPoints = points;
}

void BombEnemy::SetTarget(Duck* target) {
    m_Target = target;
}

void BombEnemy::Update(float deltaTime) {
    int dx = (m_Position.x - m_Target->GetPosition().x);
    int dy = (m_Position.y - m_Target->GetPosition().y);
    int dist = sqrt(dx * dx + dy * dy);

    if(m_CanRush && dist <= 500) {
        SetVelocity(-dx * 1.5f, -dy * 1.5f);
        m_CanRush = false;
    }

    m_Position.x += m_Velocity.x * deltaTime;
    m_Position.y += m_Velocity.y * deltaTime;
    m_Body.x = m_Position.x;
    m_Body.y = m_Position.y;

    m_Collider.Update(m_Body);
}