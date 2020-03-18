#include "doubleAttack.h"

DoubleAttack::DoubleAttack(int posX, int posY, int velX, int velY) {
    SetPosition(posX, posY);
    SetVelocity(velX, velY);
}

void DoubleAttack::Action(Duck* target) {
    target->SetShootingType(DOUBLE_SHOOT);
}