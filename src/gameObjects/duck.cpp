#include "duck.h"

Duck::Duck() {
    SetPosition(0, 0);
    SetVelocity(0, 0);
    m_Horizontal = 0;
    m_Vertical = 0;
    m_Speed = 350;
    m_Damage = 10;
    m_Score = 0; 
    m_IsShooting = false;
    m_ShootingTimer = 0.0f;
    m_ShootingType = NORMAL_SHOOT;
}

void Duck::Init(std::vector<Bullet>* projectiles) {
    m_Projectiles = projectiles;
    InitCollider();
    m_Health.Init();
}

void Duck::InitCollider() {
    m_Collider.Init(m_Body, PLAYER);
}

void Duck::SetHealth(int max) {
    m_Health.SetHealth(max);
}

void Duck::MoveHorizontal(int direction) {
    m_Horizontal = direction;
}

void Duck::MoveVertical(int direction) {
    m_Vertical = direction;
}

void Duck::Shoot() {
    Bullet projectile;
    projectile.SetPosition(m_Position.x + m_Body.w, m_Position.y + (m_Body.h / 2) - 4); // height / 2
    projectile.LoadTexture("feather", 22, 9, 1, false);
    projectile.SetVelocity(500, 0);
    projectile.InitCollider();
    m_Projectiles->push_back(Bullet(projectile));
}

void Duck::DoubleShoot() {
    Bullet projectile1, projectile2;
    projectile1.SetPosition(m_Position.x + m_Body.w, m_Position.y + (m_Body.h / 2) - 4); // height / 2
    projectile1.LoadTexture("feather", 22, 9, 1, false);
    projectile1.SetVelocity(500, -15);
    projectile1.InitCollider();
    projectile2.SetPosition(m_Position.x + m_Body.w, m_Position.y + (m_Body.h / 2) - 4); // height / 2
    projectile2.LoadTexture("feather", 22, 9, 1, false);
    projectile2.SetVelocity(500, 15);
    projectile2.InitCollider();
    m_Projectiles->push_back(Bullet(projectile1));
    m_Projectiles->push_back(Bullet(projectile2));
}

void Duck::AddPoints(int points) {
    m_Score += points;
}

void Duck::UpdateHealth(int value) {
    m_Health.UpdateHealth(value);
}

int Duck::GetScore() const {
    return m_Score;
}

int Duck::GetDamage() const {
    return m_Damage;
}

Collider Duck::GetCollider() const {
    return m_Collider;
}

int Duck::GetActualHealth() const {
    return m_Health.GetActualHealth();
}

int Duck::GetMaxHealth() const {
    return m_Health.GetMaxHealth();
}

void Duck::Movement(float deltaTime) {
    if(m_Horizontal == 1) {
        m_Velocity.x = m_Speed;
    }
    else if(m_Horizontal == -1) {
        m_Velocity.x = -m_Speed;
    }
    else {
        m_Velocity.x = 0;
    }

    if(m_Vertical == 1) {
        m_Velocity.y = m_Speed;
    }
    else if(m_Vertical == -1) {
        m_Velocity.y = -m_Speed;
    }
    else {
        m_Velocity.y = 0;
    }

    m_Position.x += m_Velocity.x * deltaTime;
    m_Position.y += m_Velocity.y * deltaTime;

    if(m_Position.x < 0) {
        m_Velocity.x = 0;
        m_Position.x = 0;
    }
    if(m_Position.x + m_Body.w > WINDOW_WIDTH) {
        m_Velocity.x = 0;
        m_Position.x = WINDOW_WIDTH - m_Body.w;
    }
    if(m_Position.y < 100) {
        m_Velocity.y = 0;
        m_Position.y = 100;
    }
    if(m_Position.y + m_Body.h > WINDOW_HEIGHT) {
        m_Velocity.y = 0;
        m_Position.y = WINDOW_HEIGHT - m_Body.h;
    }

    m_Body.x = m_Position.x;
    m_Body.y = m_Position.y;
}

void Duck::Shooting(bool shooting) {
    m_IsShooting = shooting;
}

void Duck::SetShootingType(ShootingType type) {
    m_ShootingType = type;
}

void Duck::Update(float deltaTime) {
    Movement(deltaTime);

    if(m_IsShooting) {
        switch (m_ShootingType)
        {
        case NORMAL_SHOOT:
            m_ShootingTimer += deltaTime;
            if(m_ShootingTimer >= 0.1f) {
                Shoot();
                m_ShootingTimer = 0.0f;
            }
            break;
        case DOUBLE_SHOOT:
            m_ShootingTimer += deltaTime;
            if(m_ShootingTimer >= 0.1f) {
                DoubleShoot();
                m_ShootingTimer = 0.0f;
            }
            break;
        }
    }

    m_Collider.Update(m_Body);
}

void Duck::RenderHealthBar(SDL_Renderer* renderer) {
    m_Health.Render(renderer);
}
