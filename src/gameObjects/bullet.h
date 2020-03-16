#pragma once

#include "renderable.h"
#include "../collider.h"

class Bullet : public Renderable {
private:
    Collider m_Collider;

public:
    Bullet();
    ~Bullet();
    void InitCollider();
    Collider GetCollider() const;
    void Update(float deltaTime) override;
};