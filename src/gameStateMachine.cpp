#include "gameStateMachine.h"

void GameStateMachine::PushState(std::unique_ptr<GameState> state) {
    state->OnEnter();
    m_GameStates.push_back(std::move(state));
}

void GameStateMachine::PopState() {
    if(m_GameStates.back() != nullptr) {
        m_GameStates.back()->OnExit();
        m_GameStates.pop_back();
    }
}

void GameStateMachine::InputHandler(SDL_Event event) {
    if(m_GameStates.back() != nullptr) {
        m_GameStates.back()->InputHandler(event);
    }
}

void GameStateMachine::Update(float deltaTime) {
    if(m_GameStates.back() != nullptr) {
        m_GameStates.back()->Update(deltaTime);
    }
}

void GameStateMachine::Render(SDL_Renderer* renderer) {
    if(m_GameStates.back() != nullptr) {
        m_GameStates.back()->Render(renderer);
    }
}

void GameStateMachine::Restart(std::unique_ptr<GameState> state) {
	m_GameStates.pop_back();
	state->OnEnter();
	m_GameStates.push_back(std::move(state));
}