#pragma once

#include <vector>
#include <memory>
#include "GameState.h"

class GameStateMachine {
private:
    std::vector<std::unique_ptr<GameState>> m_GameStates;

public:
    void PushState(std::unique_ptr<GameState> state);
    void PopState();
    void restart(std::unique_ptr<GameState> state);
    void InputHandler();
    void Update(float deltaTime);
    void Render(SDL_Renderer* renderer);
};