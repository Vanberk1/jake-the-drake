#pragma once

#include <vector>
#include "bullet.h"
#include "duck.h"
#include "enemy.h"

class ShooterEnemy : public Enemy {
private:
    Duck* m_Target;
    std::vector<Bullet>* m_Projectiles;
    float m_ShootTimer;
    
    void Shoot(float deltaTime);
public:
    ShooterEnemy(int posX, int posY, int velX, int velY, int points);
    void SetTarget(Duck* duck);
    void SetProjectilesVector(std::vector<Bullet>* projectiles);
    void Update(float deltaTime) override;
};