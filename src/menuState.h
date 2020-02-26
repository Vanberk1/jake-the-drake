#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <cstring>    
#include <sstream>
#include "gameState.h"
#include "gameStateMachine.h"
#include "playState.h"
#include "fontManager.h"
#include "textLabel.h"
#include "game.h"

extern FontManager fontManager;
extern GameStateMachine gameStateMachine;
extern bool IsRunning;

class MenuState : public GameState {
private:
    SDL_Renderer* m_Renderer;
    SDL_Rect m_TextPosition;
    SDL_Rect m_PlayButton;
    TextLabel m_PlayTextLabel;
    SDL_Rect m_ExitButton;
    TextLabel m_ExitTextLabel;
public:
    MenuState(SDL_Renderer* renderer);
    void OnEnter() override;
    void OnExit() override;
    void InputHandler(SDL_Event event) override;
    void Update(float deltaTime) override;
    void Render(SDL_Renderer* renderer) override;
};