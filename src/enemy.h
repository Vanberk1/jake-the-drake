#pragma once 

#include "renderable.h"
#include "collider.h"

class Enemy : public Renderable {
private:
    Collider m_Collider;
    int m_RewardPoints;
public:
    Enemy();
    Enemy(int posX, int posY, int velX, int velY);
    Collider GetCollider();
    int GetRewardPoints() const;
    void Init();
    void Update(float deltaTime) override;
    void Render(SDL_Renderer* renderer);
};