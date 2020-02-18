#pragma once

#include <SDL2/SDL.h>

class GameState {
protected:
    SDL_Renderer* m_Renderer;
public:
    virtual void OnEnter() = 0;
    virtual void OnExit() = 0;
    virtual void InputHandler() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Render(SDL_Renderer* renderer) = 0;
};