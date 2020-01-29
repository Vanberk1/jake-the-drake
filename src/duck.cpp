#include "duck.h"

Duck::Duck() {
    SetPosition(0, 0);
    SetVelocity(0, 0);

    m_Horizontal = 0;
    m_Vertical = 0;

    m_Speed = 350;
}

void Duck::Init() {
    InitCollider();
}

void Duck::InitCollider() {
    m_Collider.Init(m_Body, PLAYER);
}

void Duck::MoveHorizontal(int direction) {
    m_Horizontal = direction;
}

void Duck::MoveVertical(int direction) {
    m_Vertical = direction;
}

void Duck::Shoot(std::vector<Bullet>& projectiles) {
    Bullet projectile;
    projectile.SetPosition(m_Position.x + m_Body.w, m_Position.y + (m_Body.h / 2) - 4); // height / 2
    projectile.LoadTexture("feather", 22, 9, 1, false);
    projectile.SetVelocity(500, 0);
    projectile.InitCollider();
    projectiles.push_back(Bullet(projectile));
}

Collider Duck::GetCollider() const {
    return m_Collider;
}

void Duck::Update(float deltaTime) {
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
    if(m_Position.y < 0) {
        m_Velocity.y = 0;
        m_Position.y = 0;
    }
    if(m_Position.y + m_Body.h > WINDOW_HEIGHT) {
        m_Velocity.y = 0;
        m_Position.y = WINDOW_HEIGHT - m_Body.h;
    }

    m_Body.x = m_Position.x;
    m_Body.y = m_Position.y;

    m_Collider.Update(m_Body);
}

void Duck::Render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &m_Collider.GetCollider());
    if(m_IsAnimated) {
        m_Source.x = m_Source.w * static_cast<int>((SDL_GetTicks() / m_Animation.m_AnimationSpeed) % m_Animation.m_FramesNum);
    }
    SDL_RenderCopy(renderer, m_Texture, &m_Source, &m_Body);
}
