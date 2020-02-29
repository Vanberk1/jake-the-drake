#include "menuState.h"

MenuState::MenuState(SDL_Renderer* renderer) {
    m_Renderer = renderer;
}

void MenuState::OnEnter() {
    TTF_Font* font = fontManager.GetFont("arial", 24);
    m_PlayTextLabel.init(m_Renderer, font);
    m_ExitTextLabel.init(m_Renderer, font);

    m_PlayButton = { (WINDOW_WIDTH / 2) - 100, 100, 200, 80 };
    m_PlayTextLabel.createLabel("PLAY!", { 0, 0, 0, 255 });
    SDL_Rect* textPosition = m_PlayTextLabel.getPosition();
    textPosition->x = (m_PlayButton.x + (m_PlayButton.w / 2)) - (textPosition->w / 2);
    textPosition->y = (m_PlayButton.y + (m_PlayButton.h / 2)) - (textPosition->h / 2);
    m_PlayTextLabel.setPosition(*textPosition);
    m_PlayTextLabel.setText("PLAY!");


    m_ExitButton = { (WINDOW_WIDTH / 2) - 100, 300, 200, 80 };
    m_ExitTextLabel.createLabel("EXIT!", { 0, 0, 0, 255 }); 
    textPosition = m_ExitTextLabel.getPosition();
    textPosition->x = (m_ExitButton.x + (m_ExitButton.w / 2)) - (textPosition->w / 2);
    textPosition->y = (m_ExitButton.y + (m_ExitButton.h / 2)) - (textPosition->h / 2);
    m_ExitTextLabel.setPosition(*textPosition); 
    m_ExitTextLabel.setText("QUIT");
}

void MenuState::InputHandler(SDL_Event event) {
    if(event.type == SDL_MOUSEBUTTONDOWN) {
        if(event.button.button == SDL_BUTTON_LEFT) {
            if(event.button.x > 300 && event.button.x < 500 && event.button.y > 100 && event.button.y < 180) {
                std::cout << "Play button pressed!" << std::endl;
                gameStateMachine.PushState(std::make_unique<PlayState>(m_Renderer));
            }
            if(event.button.x > 300 && event.button.x < 500 && event.button.y > 300 && event.button.y < 380) {
                std::cout << "Exit button pressed!" << std::endl;
                IsRunning = false;
            }
        }
    }
}

void MenuState::Update(float deltaTime) {

}

void MenuState::Render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(m_Renderer, 21, 231, 91, 255);
    SDL_RenderFillRect(m_Renderer, &m_PlayButton);
    m_PlayTextLabel.draw(m_Renderer);

    SDL_SetRenderDrawColor(m_Renderer, 170, 23, 53, 255);
    SDL_RenderFillRect(m_Renderer, &m_ExitButton);
    m_ExitTextLabel.draw(m_Renderer);
}

void MenuState::OnExit() {
}