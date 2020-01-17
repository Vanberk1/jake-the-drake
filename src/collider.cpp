#include "collider.h"

void Collider::Init(SDL_Rect body, ColliderTag tag) {
    m_Collider.x = body.x;
    m_Collider.y = body.y;
    m_Collider.w = body.w;
    m_Collider.h = body.h;
    m_Tag = tag;
}

void Collider::Update(SDL_Rect body) {
    m_Collider.x = body.x;
    m_Collider.y = body.y;
    m_Collider.w = body.w;
    m_Collider.h = body.h;
}

SDL_Rect& Collider::GetCollider() {
    return m_Collider;
}

bool Collider::AABBCollision(Collider other) {
    return (
        m_Collider.x + m_Collider.w >= other.GetCollider().x &&
        other.GetCollider().x + other.GetCollider().w >= m_Collider.x &&
        m_Collider.y + m_Collider.h >= other.GetCollider().y &&
        other.GetCollider().y + other.GetCollider().h >= m_Collider.y
    );
}