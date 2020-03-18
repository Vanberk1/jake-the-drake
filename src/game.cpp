#include "game.h"

GameStateMachine gameStateMachine;
TextureManager textureManager;
FontManager fontManager;

Game::Game(int width, int height) {
    m_Width = width; 
    m_Height = height;
    IsRunning = true;
    countedFrames = 0;
    ticksLastFrame = SDL_GetTicks();
}

Game::~Game() {
}

void Game::Init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "Error initializing SDL." << std::endl;
        return;
    }
    if(TTF_Init() != 0) {
        std::cout << "Error initializing SDL_TTF !" << std::endl;
        return;
    }

    m_Window = SDL_CreateWindow(
        "Jake The Drake", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        m_Width, 
        m_Height, 
        SDL_WINDOW_SHOWN
    );
    if (!m_Window){
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, -1, 0);
    if (!m_Renderer) {
        std::cout << "Error creating SDL renderer." << std::endl;
        return;
    }

    textureManager.Init(m_Renderer);
    fontManager.Init(m_Renderer);

    LoadLevel();
}

void Game::LoadLevel() {
    textureManager.AddTexture("duck", "./assets/images/jake.png");
    textureManager.AddTexture("normal-enemy", "./assets/images/normal-enemy.png");
    textureManager.AddTexture("bomb-enemy", "./assets/images/bomb-enemy.png");
    textureManager.AddTexture("bullet", "./assets/images/bullet.png");
    textureManager.AddTexture("lilypad", "./assets/images/lilypad.png");
    textureManager.AddTexture("enemy-bullet", "./assets/images/enemy-bullet.png");
    textureManager.AddTexture("background", "./assets/images/background.png");
    textureManager.AddTexture("health-red", "./assets/images/health-red.png");
    textureManager.AddTexture("health-grey", "./assets/images/health-grey.png");
    textureManager.AddTexture("heart", "./assets/images/heart.png");
    textureManager.AddTexture("energy", "./assets/images/energy.png");
    textureManager.AddTexture("hp-up", "./assets/images/hp-up.png");
    textureManager.AddTexture("x2", "./assets/images/x2.png");

    fontManager.AddFont("arial", 24, "./assets/fonts/arial.ttf");

    gameStateMachine.PushState(std::make_unique<MenuState>(m_Renderer));
}

void Game::InputHandler() {
    while(SDL_PollEvent(&m_Event)) {
        if(m_Event.type == SDL_QUIT) {
            IsRunning = false;
        }
    }
    gameStateMachine.InputHandler(m_Event);
}

void Game::Update() {
    float deltaTime = UpdateFPS();
    gameStateMachine.Update(deltaTime);
}

void Game::Render() {
    SDL_SetRenderDrawColor(m_Renderer, 21, 21, 21, 255);
    SDL_RenderClear(m_Renderer);
    gameStateMachine.Render(m_Renderer);
    SDL_RenderPresent(m_Renderer);
}

void Game::Destroy() {
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    TTF_Quit();
    SDL_Quit();
}

float Game::UpdateFPS() {
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + (1000 / 60)));
    float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;
    deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;
    ticksLastFrame = SDL_GetTicks();

    SDL_SetRenderDrawColor(m_Renderer, 21, 21, 21, 255);
    SDL_RenderClear(m_Renderer);

    // float avgFPS = countedFrames / ( SDL_GetTicks() / 1000.f );
    // if( avgFPS > 100000 ) {
    //     avgFPS = 0;
    // }
    // std::stringstream ss;
    // ss << avgFPS;
    // std::string windowTitle = "Jake The Drake - FPS: " + ss.str();
    // SDL_SetWindowTitle(m_Window, windowTitle.c_str());

    // ++countedFrames;

    return deltaTime;
}
