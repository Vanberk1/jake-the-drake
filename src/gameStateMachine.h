#pragma once

#include <vector>
#include "playState.h"

class GameStateMachine {
private:
    std::vector<GameState*> m_GameStates;

public:
    void PushState(GameState* state);
    void PopState();
    void Update(float deltaTime);
};