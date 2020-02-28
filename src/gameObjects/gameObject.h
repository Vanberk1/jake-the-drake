#pragma once 

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../../lib/glm/glm.hpp"

class GameObject {
public:
    virtual ~GameObject() = 0;
    virtual void Update(float deltaTime) = 0;
};