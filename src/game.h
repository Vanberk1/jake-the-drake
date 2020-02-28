#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <cstring>
#include <sstream>
#include <memory>
#include <ctime>
#include "types.h"
#include "fontManager.h"
#include "gameStateMachine.h"
#include "states/menuState.h"
#include "gameObjects/gameObject.h"
#include "textureManager.h"

extern bool IsRunning;

class Game {
private:
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
    SDL_Event m_Event;
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
private:
    void LoadLevel();
    float UpdateFPS();
};