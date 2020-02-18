#include "shooterEnemy.h"

ShooterEnemy::ShooterEnemy(int posX, int posY, int velX, int velY, int points) {
    SetPosition(posX, posY);
    SetVelocity(velX, velY);

    m_ShootTimer = 1.0f;

    m_RewardPoints = points;
}

void ShooterEnemy::SetProjectilesVector(std::vector<Bullet>* projectiles) {
    m_Projectiles = projectiles;
}

void ShooterEnemy::Shoot() {
    Bullet projectile;
    projectile.SetPosition(m_Position.x - 9, m_Position.y + (m_Body.h / 2) - 4); // height / 2
    projectile.LoadTexture("feather", 22, 9, 1, false);
    projectile.SetVelocity(-200, 0);
    projectile.InitCollider();
    m_Projectiles->push_back(Bullet(projectile));
}

void ShooterEnemy::Update(float deltaTime) {
    m_Position.x += m_Velocity.x * deltaTime;
    m_Position.y += m_Velocity.y * deltaTime;
    m_Body.x = m_Position.x;
    m_Body.y = m_Position.y;

    m_ShootTimer += deltaTime;
    if(m_ShootTimer >= 1.0f) {
        std::cout << "Shoot!" << std::endl;
        Shoot();
        m_ShootTimer = 0.0f;
    }

    m_Collider.Update(m_Body);
}