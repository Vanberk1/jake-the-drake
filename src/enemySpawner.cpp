#include "enemySpawner.h"

EnemySpawner::EnemySpawner(int spawnRate, Duck* target)
    : m_SpawnRate(spawnRate), m_NormalTimer(0), m_BombTimer(10), m_Target(target) {

}

void EnemySpawner::Run(float deltaTime, std::vector<Enemy*>& enemies) {
    m_NormalTimer += deltaTime;
    m_BombTimer += deltaTime;

    // std::cout << "Normal timer: " << m_NormalTimer << std::endl;
    // std::cout << "Bomb timer: " << m_BombTimer << std::endl;

    if(m_NormalTimer >= m_SpawnRate) {
        SendWave(enemies);
        m_NormalTimer = 0;
    }

    if(m_BombTimer >= m_SpawnRate / 2) {
        SpawnBomb(enemies);
        m_BombTimer = 0;
    }
}

void EnemySpawner::SendWave(std::vector<Enemy*>& enemies) {
    int heightRNG = m_Rng.Int(0, WINDOW_HEIGHT - 40);
    int xOffSet = WINDOW_WIDTH;
    int delay = 100;
    int vel = 150;
    int waveLength = 3;
    for(int i = 0; i < 5; ++i) {
        NormalEnemy* newEnemy = new NormalEnemy(xOffSet + i * delay, heightRNG, -vel, 0, 1);   
        newEnemy->LoadTexture("croco", 76, 40, 1, false);
        newEnemy->Init();
        enemies.push_back(newEnemy);
    } 
}

void EnemySpawner::SpawnBomb(std::vector<Enemy*>& enemies) { 
    int heightRNG = m_Rng.Int(0, WINDOW_HEIGHT - 40);
    BombEnemy* bomb = new BombEnemy(WINDOW_WIDTH, heightRNG, -150, 0, 10);
    bomb->LoadTexture("croco", 76, 40, 1, false);
    bomb->Init();
    bomb->SetTarget(m_Target);
    enemies.push_back(bomb);
}