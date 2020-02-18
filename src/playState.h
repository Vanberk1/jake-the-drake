#pragma once

#include <iostream>
#include <vector>
#include <cstring>    
#include <sstream>
#include "gameState.h"
#include "util/random.h"
#include "fontManager.h"
#include "duck.h"
#include "enemy.h"
#include "enemySpawner.h"
#include "bullet.h"
#include "textLabel.h"

extern FontManager fontManager;

class PlayState: public GameState {
private:
    Duck jake;
    EnemySpawner* spawner;
    std::vector<Bullet> projectiles;
    std::vector<Enemy*> enemies;

    TextLabel scoreLabel;

    uint8_t* prevKeyState;
    const uint8_t* currentKeyState;
    int keyLength;

    bool KeyPressed(SDL_Scancode scanCode);
    bool KeyReleased(SDL_Scancode scanCode);
public:
    PlayState(SDL_Renderer* renderer);
    void OnEnter() override;
    void OnExit() override;
    void InputHandler() override;
    void Update(float deltaTime) override;
    void Render(SDL_Renderer* renderer) override;

    void PlayerEnemyCollision();
    void ProjectileEnemyCollision();
};