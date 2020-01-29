#pragma once 

#include "renderable.h"
#include "collider.h"

class Enemy : public Renderable {
private:
    Collider m_Collider;
public:
    Enemy();
    Enemy(int posX, int posY, int velX, int velY);
    Collider GetCollider();
    void Init();
    void Update(float deltaTime) override;
    void Render(SDL_Renderer* renderer);
};