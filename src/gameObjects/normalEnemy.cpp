#include "normalEnemy.h"

NormalEnemy::NormalEnemy(int posX, int posY, int velX, int velY, int points) {
    SetPosition(posX, posY);
    SetVelocity(velX, velY);

    m_RewardPoints = points;
}


void NormalEnemy::Update(float deltaTime) {
    m_Position.x += m_Velocity.x * deltaTime;
    m_Position.y += m_Velocity.y * deltaTime;
    m_Body.x = m_Position.x;
    m_Body.y = m_Position.y;

    m_Collider.Update(m_Body);
}