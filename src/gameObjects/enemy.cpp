#include "enemy.h"
#include <iostream>

void Enemy::SetHealth(int max) {
    m_MaxHealth = max;
    m_ActualHealth = max;
}

void Enemy::UpdateHealth(int value) {
    m_ActualHealth += value;
    if(m_ActualHealth < 0) {
        m_ActualHealth = 0;
    }
    if(m_ActualHealth > m_MaxHealth) {
        m_ActualHealth = m_MaxHealth;
    }
}

int Enemy::GetHealth() const {
    return m_ActualHealth;
}

int Enemy::GetRewardPoints() const {
    return m_RewardPoints;
}

Collider Enemy::GetCollider() const {
    return m_Collider;
}

void Enemy::Init() {
    m_Collider.Init(m_Body, ENEMY);
}


 