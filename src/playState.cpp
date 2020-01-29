#include "playState.h"

void PlayState::OnEnter() {
    jake.SetPosition(100, 100);
    jake.LoadTexture("duck", 21, 17, 3, true);
    jake.SetAnimation(3, 200);
    jake.Init();

    spawner = new EnemySpawner(&enemies, 200);

    currentKeyState = SDL_GetKeyboardState(&keyLength);
    prevKeyState = new uint8_t[keyLength];
    memcpy(prevKeyState, currentKeyState, keyLength);
}

void PlayState::OnExit() {

}

void PlayState::InputHandler() {
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

void PlayState::Update(float deltaTime) {
    spawner->Run();

    jake.Update(deltaTime);
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
    
    PlayerEnemyCollision();
    ProjectileEnemyCollision();
}

void PlayState::Render(SDL_Renderer* renderer) {
    jake.Render(renderer);
    for(Bullet& projectile : projectiles) {
        projectile.Render(renderer);
    }
    for(Enemy& enemy : enemies) {
        enemy.Render(renderer);
    }
}

void PlayState::PlayerEnemyCollision() {
    for(int i = 0; i < enemies.size(); ++i) {
        if(jake.GetCollider().AABBCollision(enemies[i].GetCollider())) {
           // std::cout << "Player Enemy Collision!" << std::endl;
        }
    }
}

void PlayState::ProjectileEnemyCollision() {
    for(int i = 0; i < projectiles.size(); ++i) {
        for(int j = 0; j < enemies.size(); ++j) {
            if(projectiles[i].GetCollider().AABBCollision(enemies[j].GetCollider())) {
                // std::cout << "Projectile[" << i << "] Hit Enemy[" << j << "]" << std::endl;
                enemies.erase(enemies.begin() + j);
                projectiles.erase(projectiles.begin() + i);
            }
        }
    }
}

bool PlayState::KeyPressed(SDL_Scancode scanCode) {
    return !prevKeyState[scanCode] && currentKeyState[scanCode];
}

bool PlayState::KeyReleased(SDL_Scancode scanCode) {
    return prevKeyState[scanCode] && !currentKeyState[scanCode];
}