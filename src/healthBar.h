#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "textureManager.h"

extern TextureManager textureManager;

class HealthBar {
private:
    SDL_Rect m_Position;
    SDL_Texture* m_Red;
    SDL_Texture* m_Grey;
    SDL_Texture* m_Heart;
    SDL_Texture* m_Energy;
    int m_Scale;
    int m_ActualHealth;
    int m_MaxHealth;
public:
    HealthBar();
    void Init();
    void SetHealth(int max);
    void UpdateHealth(int value);
    void Update(float deltaTime);
    void Render(SDL_Renderer* renderer);

    int GetActualHealth() const;
    int GetMaxHealth() const;
};