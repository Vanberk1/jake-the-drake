#pragma once 

#include "renderable.h"
#include "../collider.h"

class Enemy : public Renderable {
protected:
    Collider m_Collider;
    int m_RewardPoints;
    int m_ActualHeal;
    int m_MaxHeal;
public:
    Collider GetCollider();
    int GetRewardPoints() const;
    int GetHeal() const;
    void SetHeal(int max);
    void UpdateHeal(int value);
    void Init();
    virtual void Update(float deltaTime) = 0;
    void Render(SDL_Renderer* renderer);
};