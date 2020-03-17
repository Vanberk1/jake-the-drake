#include "healthUp.h"

HealthUp::HealthUp(int posX, int posY, int velX, int velY) {
    SetPosition(posX, posY);
    SetVelocity(velX, velY);
}

void HealthUp::Action(Duck* target) {
    target->UpdateHealth(1);
}