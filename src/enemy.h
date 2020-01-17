#pragma once 

#include "rendereable.h"
#include "collider.h"

class Enemy : public Rendereable {
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