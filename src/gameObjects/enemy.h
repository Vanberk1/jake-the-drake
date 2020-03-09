#pragma once 

#include "renderable.h"
#include "../collider.h"

class Enemy : public Renderable {
protected:
    Collider m_Collider;
    int m_RewardPoints;
    int m_ActualHealth;
    int m_MaxHealth;
public:
    Collider GetCollider();
    int GetRewardPoints() const;
    int GetHealth() const;
    void SetHealth(int max);
    void UpdateHealth(int value);
    void Init();
    virtual void Update(float deltaTime) = 0;
    void Render(SDL_Renderer* renderer);
};