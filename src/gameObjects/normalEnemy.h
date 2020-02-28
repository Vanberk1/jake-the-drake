#pragma once

#include "enemy.h"

class NormalEnemy : public Enemy {
public:
    NormalEnemy(int posX, int posY, int velX, int velY, int points);
    void Update(float deltaTime) override;
};