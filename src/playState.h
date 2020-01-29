#pragma once

#include <iostream>
#include <vector>
#include <cstring>    
#include "gameState.h"
#include "duck.h"
#include "enemy.h"
#include "enemySpawner.h"
#include "bullet.h"

class PlayState: public GameState {
private:
    Duck jake;
    Enemy testEnemy;
    EnemySpawner* spawner;
    std::vector<Bullet> projectiles;
    std::vector<Enemy> enemies;

    uint8_t* prevKeyState;
    const uint8_t* currentKeyState;
    int keyLength;

    bool KeyPressed(SDL_Scancode scanCode);
    bool KeyReleased(SDL_Scancode scanCode);
public:
    void OnEnter() override;
    void OnExit() override;
    void InputHandler() override;
    void Update(float deltaTime) override;
    void Render(SDL_Renderer* renderer) override;

    void PlayerEnemyCollision();
    void ProjectileEnemyCollision();
};