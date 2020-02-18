#pragma once

#include <vector>
#include "bullet.h"
#include "enemy.h"

class ShooterEnemy : public Enemy {
private:
    std::vector<Bullet>* m_Projectiles;
    float m_ShootTimer;
public:
    ShooterEnemy(int posX, int posY, int velX, int velY, int points);
    void Shoot();
    void SetProjectilesVector(std::vector<Bullet>* projectiles);
    void Update(float deltaTime) override;
};