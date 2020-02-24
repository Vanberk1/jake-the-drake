#include "bombEnemy.h"

BombEnemy::BombEnemy(int posX, int posY, int velX, int velY, int points) {
    SetPosition(posX, posY);
    SetVelocity(velX, velY);
    m_Stop = true;
    m_CanRush = false;
    m_Rush = false;
    m_StopTimer = 0.0f;
    m_RewardPoints = points;
}

void BombEnemy::SetTarget(Duck* target) {
    m_Target = target;
}

void BombEnemy::Update(float deltaTime) {
    int dx = (m_Position.x - m_Target->GetPosition().x);
    int dy = (m_Position.y - m_Target->GetPosition().y);
    int dist = sqrt(dx * dx + dy * dy);

    if(!m_Rush && m_Stop && dist <= 500 && m_Position.x <= WINDOW_WIDTH - 100) {
        SetVelocity(0, 0);
        m_Stop = false;
    }

    if(!m_Stop) {
        m_StopTimer += deltaTime;
        if(m_StopTimer >= 0.5f) {
            m_CanRush = true;
            m_Stop = true;
        }
    }

    if(m_CanRush) {
        SetVelocity(-dx * 1.5f, -dy * 1.5f);
        m_CanRush = false;
        m_Rush = true;
    }

    // if(m_CanRush && dist <= 500) {
    //     SetVelocity(0, 0);
    //     m_StopTimer += deltaTime;
    //     if(m_StopTimer >= 1000.0f) {
    //         m_CanRush = true;
    //     }
    // }

    // if(m_CanRush) {
    //     SetVelocity(-dx * 1.5f, -dy * 1.5f);
    //     m_CanRush = false;
    // }

    m_Position.x += m_Velocity.x * deltaTime;
    m_Position.y += m_Velocity.y * deltaTime;
    m_Body.x = m_Position.x;
    m_Body.y = m_Position.y;

    m_Collider.Update(m_Body);
}