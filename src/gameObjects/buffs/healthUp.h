#pragma once

#include "buff.h"

class HealthUp : public Buff {
public:
    HealthUp(int posX, int posY, int velX, int velY);
    void Action(Duck* target) override;
};