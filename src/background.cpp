#include "background.h"

Background::Background() {

}

void Background::Init(std::string name, int speed, int width, int height) {
    SetBackgroundImage(name);
    SetSpeed(speed);
    m_Poisition.x = 0;
    m_Poisition.y = 0;
    m_Poisition.w = WINDOW_WIDTH * 2;
    m_Poisition.h = WINDOW_HEIGHT;
}

void Background::Update(float deltaTime) {
    if(m_Poisition.x + m_Poisition.w <= WINDOW_WIDTH) {
        m_Poisition.x = 0;
    }
    m_Poisition.x += m_Speed * deltaTime;
}

void Background::Render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, m_BackgroundImage, NULL, &m_Poisition);
}

void Background::SetBackgroundImage(std::string name) {
    m_BackgroundImage = textureManager.GetTexture(name);
}

void Background::SetSpeed(int speed) {
    m_Speed = speed;
}