#pragma once

#include "rendereable.h"
#include "collider.h"
#include "bullet.h"
#include <vector>

class Duck : public Rendereable {
private:
    int m_Horizontal;
    int m_Vertical;
    Collider m_Collider;

public:
    Duck();
    void Init();
    void InitCollider();
    void MoveHorizontal(int direction);
    void MoveVertical(int direction);

    void Shoot(std::vector<Bullet>& projectiles);

    Collider GetCollider() const;

    void Update(float deltaTime) override;
    void Render(SDL_Renderer* renderer);
};