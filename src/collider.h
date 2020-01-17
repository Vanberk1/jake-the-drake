#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include "types.h"

class Collider {
private:
    ColliderTag m_Tag;
    SDL_Rect m_Collider;

public:
    void Init(SDL_Rect body, ColliderTag tag);
    SDL_Rect& GetCollider();
    void Update(SDL_Rect body);
    void Render(SDL_Renderer* renderer);
    bool AABBCollision(Collider other);
};