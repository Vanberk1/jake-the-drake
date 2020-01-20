#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <cstring>
#include <sstream>
#include <ctime>
#include "gameObject.h"
#include "duck.h"
#include "enemy.h"
#include "bullet.h"
#include "textureManager.h"
#include "enemySpawner.h"

class Game {
private:
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
    SDL_Event m_Event;
    bool m_IsRunning;
    int m_Width;
    int m_Height;
    int ticksLastFrame;
    int countedFrames;

    Duck jake;
    Enemy testEnemy;
    EnemySpawner* spawner;
    std::vector<Bullet> projectiles;

public:
    Game(int width, int height);
    ~Game();
    void Init();
    void InputHandler();
    void Update();
    void Render();
    void Destroy();

    inline bool IsRunning() const { return m_IsRunning; };
    
    std::vector<Enemy> enemies;

private:
    uint8_t* prevKeyState;
    const uint8_t* currentKeyState;
    int keyLength;
    int spawnTimer;

    void LoadLevel();
    bool KeyPressed(SDL_Scancode scanCode);
    bool KeyReleased(SDL_Scancode scanCode);
    float UpdateFPS();
    void PlayerEnemyCollision();
    void ProjectileEnemyCollision();
};