#include "background.h"

Background::Background() {

}

void Background::Init(std::string name, int speed, int width, int height) {
    SetBackgroundImage(name);
    SetSpeed(speed);
    m_Source.x = 0;
    m_Source.y = 0;
    m_Source.w = width;
    m_Source.h = height;
    m_Poisition.x = 0;
    m_Poisition.y = 0;
    m_Poisition.w = WINDOW_WIDTH;
    m_Poisition.h = WINDOW_HEIGHT;
}

void Background::Update(float deltaTime) {
    m_Poisition.x += m_Speed * deltaTime;
}

void Background::Render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, m_BackgroundImage, &m_Source, &before);
    SDL_RenderCopy(renderer, m_BackgroundImage, &m_Source, &m_Poisition);
    SDL_RenderCopy(renderer, m_BackgroundImage, &m_Source, &after);
}

void Background::SetBackgroundImage(std::string name) {
    m_BackgroundImage = textureManager.GetTexture(name);
}

void Background::SetSpeed(int speed) {
    m_Speed = speed;
}