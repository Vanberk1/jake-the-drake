#include "animation.h"

Animation::Animation() {

}

Animation::Animation(int framesNum, int animationSpeed, int animationCount)
    : m_FramesNum(framesNum), m_AnimationSpeed(animationSpeed), m_AnimationCount(animationCount) {
}
