#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <cstring>
#include <sstream>
#include <ctime>
#include "gameObject.h"
#include "types.h"
#include "gameStateMachine.h"
#include "textureManager.h"

class Game {
private:
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
    SDL_Event m_Event;
    bool m_IsRunning;
    int m_Width;
    int m_Height;
    int ticksLastFrame;
    int countedFrames;
public:
    Game(int width, int height);
    ~Game();
    void Init();
    void InputHandler();
    void Update();
    void Render();
    void Destroy();

    inline bool IsRunning() const { return m_IsRunning; };
private:
    void LoadLevel();
    float UpdateFPS();
};