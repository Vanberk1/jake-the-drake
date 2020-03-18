#pragma once

#include "buff.h"

class DoubleAttack : public Buff {
public:
    DoubleAttack(int posX, int posY, int velX, int velY);
    void Action(Duck* target) override;
};