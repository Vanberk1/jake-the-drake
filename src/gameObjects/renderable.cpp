#include "renderable.h"

void Renderable::LoadTexture(std::string name, int width, int height, int scale, bool isAnimated) {
    m_Texture = textureManager.GetTexture(name);
    m_Scale = scale;
    m_Source.x = 0;
    m_Source.y = 0;
    m_Source.w = width;
    m_Source.h = height;
    m_Body.x = m_Position.x;
    m_Body.y = m_Position.y;
    m_Body.w = width * scale;
    m_Body.h = height * scale;
    m_IsAnimated = isAnimated;
    m_Clip = false;
    index = 0;
}

void Renderable::AddAnimation(std::string animName, int framesNum, int animationSpeed, int animationCount) {
    if(m_Animations.find(animName) == m_Animations.end()) {
        m_Animations.insert(std::pair<std::string, Animation>(animName, { framesNum, animationSpeed, animationCount }));
        // std::cout << "Animation["<< animationCount << "]: " << animName << "[f:" << framesNum << ",s:" << animationSpeed << "] ADDED!" << std::endl;
    }
    else {
        m_Animations[animName] = { framesNum, animationSpeed, animationCount };
        // std::cout << "Animation: " << animName << "[f:" << framesNum << ",s:" << animationSpeed << "] CHANGED!" << std::endl;
    }
    m_ActualAnimation = animName;
}

void Renderable::SetAnimation(std::string animName) {
    if(m_Animations.find(animName) != m_Animations.end()) {
        m_ActualAnimation = animName;
        index = 0;
        // std::cout << "Animation: " << animName << " changed" << std::endl;
    }
    else {
        // std::cout << "Animation: " << animName << " not found!" << std::endl;
    }
}

void Renderable::PlayAnimation(std::string animName) {
    if(m_Animations.find(animName) != m_Animations.end()) {
        // std::cout << animName << std::endl; 
        m_ClipAnimation = animName;
        m_Clip = true;
        // std::cout << m_ClipAnimation << " " << m_Animations[animName].FramesNum << " " << m_Clip << std::endl;
        index = 0;
    }
}

void Renderable::Render(SDL_Renderer* renderer) {
    if(m_IsAnimated) {
        if(!m_Clip) {
            m_Source.x = m_Source.w * static_cast<int>((index / m_Animations[m_ActualAnimation].AnimationSpeed) % m_Animations[m_ActualAnimation].FramesNum);
            m_Source.y = m_Source.h * m_Animations[m_ActualAnimation].AnimationCount;
            index += 1;
        }
        else {
            int frame = static_cast<int>((index / m_Animations[m_ClipAnimation].AnimationSpeed) % m_Animations[m_ClipAnimation].FramesNum);
            // std::cout << "Actual frame: " << frame << std::endl;
            m_Source.x = m_Source.w * frame;
            m_Source.y = m_Source.h * m_Animations[m_ClipAnimation].AnimationCount;
            if(frame >= m_Animations[m_ClipAnimation].FramesNum - 1) {
                m_Clip = false;
            }
            index += 1;
        }
    }
    SDL_RenderCopy(renderer, m_Texture, &m_Source, &m_Body);
}

glm::vec2 Renderable::GetPosition() const {
    return m_Position;
}

glm::vec2 Renderable::GetVelocity() const {
    return m_Velocity;
}

int Renderable::GetWidth() const {
    return m_Body.w;
}

int Renderable::GetHeight() const {
    return m_Body.h;
}

int Renderable::GetScale() const {
    return m_Scale;
}

void Renderable::SetPosition(float posX, float posY) {
    m_Position.x = posX;
    m_Position.y = posY;
}

void Renderable::SetVelocity(float velX, float velY) {
    m_Velocity.x = velX;
    m_Velocity.y = velY;
}

void Renderable::SetScale(int scale) {
    m_Scale = scale;
}