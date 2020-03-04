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
}

void Duck::Init(std::vector<Bullet>* projectiles) {
    m_Projectiles = projectiles;
    InitCollider();
}

void Duck::InitCollider() {
    m_Collider.Init(m_Body, PLAYER);
}

void Duck::SetHeal(int max) {
    m_MaxHeal = max;
    m_ActualHeal = max;
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

void Duck::AddPoints(int points) {
    m_Score += points;
}

void Duck::UpdateHeal(int value) {
    m_ActualHeal += value;
    if(m_ActualHeal < 0) {
        m_ActualHeal = 0;
    }
    if(m_ActualHeal > m_MaxHeal) {
        m_ActualHeal = m_MaxHeal;
    }
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

int Duck::GetActualHeal() const {
    return m_ActualHeal;
}

int Duck::GetMaxHeal() const {
    return m_MaxHeal;
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

void Duck::Update(float deltaTime) {
    Movement(deltaTime);

    if(m_IsShooting) {
        m_ShootingTimer += deltaTime;
        if(m_ShootingTimer >= 0.1f) {
            Shoot();
            m_ShootingTimer = 0.0f;
        }
    }

    m_Collider.Update(m_Body);
}

void Duck::Render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &m_Collider.GetCollider());
    if(m_IsAnimated) {
        m_Source.x = m_Source.w * static_cast<int>((SDL_GetTicks() / m_Animations[m_ActualAnimation].m_AnimationSpeed) % m_Animations[m_ActualAnimation].m_FramesNum);
        m_Source.y = m_Source.h * m_Animations[m_ActualAnimation].m_AnimationCount;
    }
    SDL_RenderCopy(renderer, m_Texture, &m_Source, &m_Body);
}
