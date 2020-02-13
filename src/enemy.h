#pragma once 

#include "renderable.h"
#include "collider.h"

class Enemy : public Renderable {
protected:
    Collider m_Collider;
    int m_RewardPoints;
public:
    Collider GetCollider();
    int GetRewardPoints() const;
    void Init();
    virtual void Update(float deltaTime) = 0;
    void Render(SDL_Renderer* renderer);
};