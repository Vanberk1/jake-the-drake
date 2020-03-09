#include "background.h"

Background::Background() {

}

void Background::Init(std::string name, int speed, int width, int height) {
    SetBackgroundImage(name);
    SetSpeed(speed);
    m_Position.x = 0;
    m_Position.y = 0;
    m_Position.w = WINDOW_WIDTH * 2;
    m_Position.h = WINDOW_HEIGHT;
}

void Background::Update(float deltaTime) {
    if(m_Position.x + m_Position.w <= WINDOW_WIDTH) {
        m_Position.x = 0;
    }
    m_Position.x += m_Speed * deltaTime;
}

void Background::Render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, m_BackgroundImage, NULL, &m_Position);
}

void Background::SetBackgroundImage(std::string name) {
    m_BackgroundImage = textureManager.GetTexture(name);
}

void Background::SetSpeed(int speed) {
    m_Speed = speed;
}