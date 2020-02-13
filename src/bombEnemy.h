#pragma once

#include <math.h> 
#include "enemy.h"
#include "duck.h"

class BombEnemy : public Enemy {
private:
    Duck* m_Target;
    bool m_CanRush;
public:
    BombEnemy(int posX, int posY, int velX, int velY, int points);
    void SetTarget(Duck* duck);
    void Update(float deltaTime) override;
};