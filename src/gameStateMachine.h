#pragma once

#include <vector>
#include <memory>
#include "gameState.h"

class GameStateMachine {
private:
    std::vector<std::unique_ptr<GameState>> m_GameStates;
public:
    void PushState(std::unique_ptr<GameState> state);
    void PopState();
    void Restart(std::unique_ptr<GameState> state);
    void InputHandler(SDL_Event event);
    void Update(float deltaTime);
    void Render(SDL_Renderer* renderer);
};