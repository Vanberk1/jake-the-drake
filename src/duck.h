#pragma once

#include <vector>
#include "renderable.h"
#include "collider.h"
#include "bullet.h"

class Duck : public Renderable {
private:
    int m_Horizontal;
    int m_Vertical;
    Collider m_Collider;
    int m_Speed;
    int m_Score;
    std::vector<Bullet>* m_Projectiles;

public:
    Duck();
    void Init(std::vector<Bullet>* projectiles);
    void InitCollider();
    void MoveHorizontal(int direction);
    void MoveVertical(int direction);
    void Shoot();
    void Update(float deltaTime) override;
    void Render(SDL_Renderer* renderer);
    void AddPoints(int points);
    int GetScore() const;
    Collider GetCollider() const;
};