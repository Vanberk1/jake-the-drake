#pragma once

#include <vector>
#include "renderable.h"
#include "bullet.h"
#include "../healthBar.h"
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
    HealthBar m_Health;
    ShootingType m_ShootingType;

    void Movement(float deltaTime);
    void Shoot();
    void DoubleShoot();
public:
    Duck();
    void Init(std::vector<Bullet>* projectiles);
    void InitCollider();
    void SetHealth(int max);
    void UpdateHealth(int value);
    void MoveHorizontal(int direction);
    void MoveVertical(int direction);
    void Shooting(bool shooting);
    void SetShootingType(ShootingType type);
    void Update(float deltaTime) override;
    void RenderHealthBar(SDL_Renderer* renderer);
    void AddPoints(int points);
    int GetScore() const;
    int GetDamage() const;
    Collider GetCollider() const;
    int GetActualHealth() const;
    int GetMaxHealth() const;
};