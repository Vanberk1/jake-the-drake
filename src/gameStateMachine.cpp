#include "gameStateMachine.h"

void GameStateMachine::PushState(GameState* state) {
    state->OnEnter();
    m_GameStates.emplace_back(state);
}

void GameStateMachine::PopState() {
    if(!m_GameStates.empty()) {
        m_GameStates.back()->OnExit();
        m_GameStates.pop_back();
    }
}

void GameStateMachine::InputHandler() {
    if(!m_GameStates.empty()) {
        m_GameStates.back()->InputHandler();
    }
}

void GameStateMachine::Update(float deltaTime) {
    if(!m_GameStates.empty()) {
        m_GameStates.back()->Update(deltaTime);
    }
}

void GameStateMachine::Render(SDL_Renderer* renderer) {
    if(!m_GameStates.empty()) {
        m_GameStates.back()->Render(renderer);
    }
}