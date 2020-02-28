#pragma once

#include <vector>
#include "renderable.h"
#include "bullet.h"
#include "../collider.h"

class Duck : public Renderable {
private:
    int m_Horizontal;
    int m_Vertical;
    Collider m_Collider;
    int m_Speed;
    int m_Damage;
    int m_Score;
    std::vector<Bullet>* m_Projectiles;
    bool m_IsShooting;
    float m_ShootingTimer;

    void Movement(float deltaTime);
    void Shoot();
public:
    Duck();
    void Init(std::vector<Bullet>* projectiles);
    void InitCollider();
    void MoveHorizontal(int direction);
    void MoveVertical(int direction);
    void Shooting(bool shooting);
    void Update(float deltaTime) override;
    void Render(SDL_Renderer* renderer);
    void AddPoints(int points);
    int GetScore() const;
    int GetDamage() const;
    Collider GetCollider() const;
};