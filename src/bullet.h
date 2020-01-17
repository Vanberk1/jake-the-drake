#pragma once

#include "rendereable.h"
#include "collider.h"

class Bullet : public Rendereable {
private:
    Collider m_Collider;

public:
    Bullet();
    ~Bullet();
    void InitCollider();
    Collider GetCollider() const;
    void Update(float deltaTime) override;
    void Render(SDL_Renderer* renderer);
};