#pragma once

#include "../renderable.h" 
#include "../duck.h"

class Buff : public Renderable {
private:
    Collider m_Collider;
public:
    void Init();
    void Update(float deltaTime) override;
    virtual void Action(Duck* target) = 0;
    Collider GetCollider() const;
};