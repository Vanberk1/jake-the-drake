#include "shooterEnemy.h"

ShooterEnemy::ShooterEnemy(int posX, int posY, int velX, int velY, int points) {
    SetPosition(posX, posY);
    SetVelocity(velX, velY);

    m_ShootTimer = 0.0f;

    m_RewardPoints = points;
}

void ShooterEnemy::SetTarget(Duck* target) {
    m_Target = target;
}

void ShooterEnemy::SetProjectilesVector(std::vector<Bullet>* projectiles) {
    m_Projectiles = projectiles;
}

void ShooterEnemy::Shoot() {
    float dx = (m_Target->GetPosition().x - m_Position.x);
    float dy = (m_Target->GetPosition().y - m_Position.y);
    float dist = sqrt(dx * dx + dy * dy);
    // std::cout << "dx: " << dx << " - dy: " << dy << " - dist: " << dist << std::endl;
    Bullet projectile;
    projectile.SetPosition(m_Position.x - 9, m_Position.y + (m_Body.h / 2) - 4); // height / 2
    projectile.LoadTexture("feather", 22, 9, 1, false);
    dx /= dist;
    dy /= dist;
    projectile.SetVelocity(dx * 200.0f, dy * 200.0f);
    projectile.InitCollider();
    m_Projectiles->push_back(Bullet(projectile));
}

void ShooterEnemy::Update(float deltaTime) {
    m_Position.x += m_Velocity.x * deltaTime;
    m_Position.y += m_Velocity.y * deltaTime;
    m_Body.x = m_Position.x;
    m_Body.y = m_Position.y;

    m_ShootTimer += deltaTime;
    if(m_ShootTimer >= 1.5f) {
        Shoot();
        m_ShootTimer = 0.0f;
    }

    m_Collider.Update(m_Body);
}