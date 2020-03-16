#pragma once

class Animation {
public:
    int FramesNum;
    int AnimationSpeed;
    int AnimationCount;

    Animation();
    Animation(int framesNum, int animationSpeed, int animationCount);
};