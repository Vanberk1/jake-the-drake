#include "game.h"

TextureManager textureManager;

Game::Game(int width, int height) {
    m_Width = width; 
    m_Height = height;
    m_IsRunning = true;
    countedFrames = 0;
    ticksLastFrame = SDL_GetTicks();
    spawnTimer = 0;
}

Game::~Game() {
    delete spawner;
}

float Game::UpdateFPS() {
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + (1000 / 60)));
    float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;
    deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;
    ticksLastFrame = SDL_GetTicks();

    SDL_SetRenderDrawColor(m_Renderer, 21, 21, 21, 255);
    SDL_RenderClear(m_Renderer);

    float avgFPS = countedFrames / ( SDL_GetTicks() / 1000.f );
    if( avgFPS > 100000 ) {
        avgFPS = 0;
    }
    std::stringstream ss;
    ss << avgFPS;
    std::string windowTitle = "Jake The Drake - FPS: " + ss.str();
    SDL_SetWindowTitle(m_Window, windowTitle.c_str());

    ++countedFrames;

    return deltaTime;
}

void Game::Init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "Error initializing SDL." << std::endl;
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

    currentKeyState = SDL_GetKeyboardState(&keyLength);
    prevKeyState = new uint8_t[keyLength];
    memcpy(prevKeyState, currentKeyState, keyLength);

    textureManager.Init(m_Renderer);
    spawner = new EnemySpawner(&enemies, 200);

    LoadLevel();
}

void Game::LoadLevel() {
    textureManager.AddTexture("duck", "./assets/images/jake.png");
    textureManager.AddTexture("croco", "./assets/images/croco.png");
    textureManager.AddTexture("feather", "./assets/images/feather.png");

    jake.SetPosition(100, 100);
    jake.LoadTexture("duck", 30, 30, 1);
    jake.Init();

    spawner->SendWave();

    srand(time(NULL));

    // for(int i = 0; i < 5; ++i) {
    //     int heightRNG = rand() % WINDOW_HEIGHT;
    //     int widthRNG = rand() % 100 + WINDOW_WIDTH;
    //     int velRNG = rand() % 150 + 50;
    //     Enemy newEnemy(widthRNG, heightRNG, -velRNG, 0);
    //     newEnemy.LoadTexture("croco", 76, 40, 1);
    //     newEnemy.Init();
    //     enemies.emplace_back(newEnemy);
    // }

    // Enemy enemy;
    // enemy.SetPosition(200, 200);
    // enemy.SetVelocity(-100, 0);
    // enemy.LoadTexture(m_Renderer, "./assets/images/croco.png", 38, 20);
    // enemies.emplace_back(enemy);
}

void Game::InputHandler() {
    while(SDL_PollEvent(&m_Event)) {
        if(m_Event.type == SDL_QUIT) {
            m_IsRunning = false;
        }
        if(m_Event.key.keysym.sym == SDLK_ESCAPE) {
            m_IsRunning = false;
        }
    }

    if(KeyPressed(SDL_SCANCODE_W)) {
        jake.MoveVertical(-1);
    }
    if(KeyPressed(SDL_SCANCODE_A)) {
        jake.MoveHorizontal(-1);
    }
    if(KeyPressed(SDL_SCANCODE_S)) {
        jake.MoveVertical(1);
    }
    if(KeyPressed(SDL_SCANCODE_D)) {
        jake.MoveHorizontal(1);
    }
    if(KeyPressed(SDL_SCANCODE_SPACE)) {
        jake.Shoot(projectiles);
    }
    
    if(KeyReleased(SDL_SCANCODE_W)) {
        jake.MoveVertical(0);
    }
    if(KeyReleased(SDL_SCANCODE_A)) {
        jake.MoveHorizontal(0);
    }
    if(KeyReleased(SDL_SCANCODE_S)) {
        jake.MoveVertical(0);
    }
    if(KeyReleased(SDL_SCANCODE_D)) {
        jake.MoveHorizontal(0);
    }

    memcpy(prevKeyState, currentKeyState, keyLength);
}

void Game::PlayerEnemyCollision() {
    for(int i = 0; i < enemies.size(); ++i) {
        if(jake.GetCollider().AABBCollision(enemies[i].GetCollider())) {
            std::cout << "Player Enemy Collision!" << std::endl;
        }
    }
}

void Game::ProjectileEnemyCollision() {
    for(int i = 0; i < projectiles.size(); ++i) {
        for(int j = 0; j < enemies.size(); ++j) {
            if(projectiles[i].GetCollider().AABBCollision(enemies[j].GetCollider())) {
                std::cout << "Projectile[" << i << "] Hit Enemy[" << j << "]" << std::endl;
                enemies.erase(enemies.begin() + j);
                projectiles.erase(projectiles.begin() + i);
            }
        }
    }
}

void Game::Update() {
    float deltaTime = UpdateFPS();

    // std::cout << deltaTime << std::endl;

    jake.Update(deltaTime);
    // testEnemy.Update(deltaTime);
    for(int i = 0; i < projectiles.size(); ++i) {
        projectiles[i].Update(deltaTime);
        
        if(projectiles[i].GetPosition().x > WINDOW_WIDTH) {
            projectiles.erase(projectiles.begin() + i);
        }

    }
    for(int i = 0; i < enemies.size(); ++i) {
        enemies[i].Update(deltaTime);
        if(enemies[i].GetPosition().x + enemies[i].GetWidth() < 0) {
            enemies.erase(enemies.begin() + i);
        }
    }

    // if(spawnTimer < 100) {
    //     spawnTimer++;
    // }

    // if(spawnTimer >= 100) {
        spawner->Run();
    //     spawnTimer = 0;
    // }

    PlayerEnemyCollision();
    ProjectileEnemyCollision();

    // std::cout << "Projectiles: " << projectiles.size() << std::endl;
    // std::cout << "Cocrodiles: " << enemies.size() << std::endl;
}

void Game::Render() {
    SDL_SetRenderDrawColor(m_Renderer, 21, 21, 21, 255);
    SDL_RenderClear(m_Renderer);

    jake.Render(m_Renderer);
    // testEnemy.Render(m_Renderer);
    for(Bullet& projectile : projectiles) {
        projectile.Render(m_Renderer);
    }
    for(Enemy& enemy : enemies) {
        enemy.Render(m_Renderer);
    }



    SDL_RenderPresent(m_Renderer);
}

void Game::Destroy() {
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}

bool Game::KeyPressed(SDL_Scancode scanCode) {
    return !prevKeyState[scanCode] && currentKeyState[scanCode];
}

bool Game::KeyReleased(SDL_Scancode scanCode) {
    return prevKeyState[scanCode] && !currentKeyState[scanCode];
}