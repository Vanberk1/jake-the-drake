#pragma once

#include <iostream>
#include <vector>
#include <cstring>    
#include <sstream>
#include "gameState.h"
#include "../background.h"
#include "../enemySpawner.h"
#include "../fontManager.h"
#include "../textLabel.h"
#include "../game.h"
#include "../gameObjects/duck.h"
#include "../gameObjects/enemy.h"
#include "../gameObjects/bullet.h"
#include "../gameObjects/buffs/healthUp.h"
#include "../gameObjects/buffs/doubleAttack.h"
#include "../util/random.h"

extern FontManager fontManager;

class PlayState : public GameState {
private:
    bool m_IsPaused;
    bool m_GameOver;
    Random m_Rng;

    Background background;

    Duck jake;
    EnemySpawner* spawner;
    std::vector<Bullet> projectiles;
    std::vector<Bullet> enemyProjectiles;
    std::vector<Enemy*> enemies;
    std::vector<Buff*> buffs;

    TextLabel m_HealthText;
    TextLabel m_ScoreLabel;
    TextLabel m_PauseText;
    TextLabel m_GameOverText;
	TextLabel m_RestartText;

    uint8_t* prevKeyState;
    const uint8_t* currentKeyState;
    int keyLength;

    bool KeyPressed(SDL_Scancode scanCode);
    bool KeyReleased(SDL_Scancode scanCode);
    bool IsKeyPressed(SDL_Scancode scanCode);
public:
    PlayState(SDL_Renderer* renderer);
    void OnEnter() override;
    void OnExit() override;
    void InputHandler(SDL_Event event) override;
    void Update(float deltaTime) override;
    void Render(SDL_Renderer* renderer) override;

    void PlayerEnemyCollision();
    void PlayerBuffsCollision();
    void ProjectilePlayerCollision();
    void ProjectileEnemyCollision();
    void BulletCollision();
};