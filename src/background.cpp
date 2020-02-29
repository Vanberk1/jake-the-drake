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
    m_Body.x = 0;
    m_Body.y = 0;
    m_Body.w = WINDOW_WIDTH;
    m_Body.h = WINDOW_HEIGHT;
    
}

void Background::Update(float deltaTime) {
    // m_Body.x += m_Speed * deltaTime;
}

void Background::Render(SDL_Renderer* renderer) {
    // SDL_Rect before = { m_Body.x - m_Body.w, 0, m_Body.w, m_Body.h };
    // SDL_Rect after = { m_Body.x + m_Body.w, 0, m_Body.w, m_Body.h };
    // SDL_RenderCopy(renderer, m_BackgroundImage, &m_Source, &before);
    SDL_RenderCopy(renderer, m_BackgroundImage, &m_Source, &m_Body);
    // SDL_RenderCopy(renderer, m_BackgroundImage, &m_Source, &after);
}

void Background::SetBackgroundImage(std::string name) {
    m_BackgroundImage = textureManager.GetTexture(name);
}

void Background::SetSpeed(int speed) {
    m_Speed = speed;
}