#pragma once

class Animation {
public:
    int m_FramesNum;
    int m_AnimationSpeed;
    int m_AnimationCount;

    Animation();
    Animation(int framesNum, int animationSpeed, int animationCount);
};