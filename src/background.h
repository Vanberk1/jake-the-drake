#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "textureManager.h"
#include "types.h"

extern TextureManager textureManager;

class Background {
private:
    SDL_Texture* m_BackgroundImage;
    int m_Speed;
    SDL_Rect m_Source;
    SDL_Rect m_Body;
public:
    Background();
    void Init(std::string name, int speed, int width, int height);
    void Update(float deltaTime);
    void Render(SDL_Renderer* renderer);
    void SetBackgroundImage(std::string name);
    void SetSpeed(int speed);
};