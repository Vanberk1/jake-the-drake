#include "enemySpawner.h"

EnemySpawner::EnemySpawner(int spawnRate, Duck* target, std::vector<Bullet>* projectiles)
    : m_SpawnRate(spawnRate), m_NormalTimer(0.0f), m_BombTimer(10.0f), m_Target(target)
    , m_Projectiles(projectiles), m_ShooterTimer(10.0f) {

}

void EnemySpawner::Run(float deltaTime, std::vector<Enemy*>& enemies) {
    m_NormalTimer += deltaTime;
    m_BombTimer += deltaTime;
    m_ShooterTimer += deltaTime;

    // std::cout << "Normal timer: " << m_NormalTimer << std::endl;
    // std::cout << "Bomb timer: " << m_BombTimer << std::endl;

    // if(m_NormalTimer >= m_SpawnRate / 2) {
    //     SendWave(enemies);
    //     m_NormalTimer = 0;
    // }

    // if(m_BombTimer >= m_SpawnRate / 2) {
    //     SpawnBomb(enemies);
    //     m_BombTimer = 0;
    // }

    if(m_ShooterTimer >= m_SpawnRate / 3.0f) {
        SpawnShooter(enemies);
        m_ShooterTimer = 0;
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

void EnemySpawner::SpawnShooter(std::vector<Enemy*>& enemies) {
    int heightRNG = m_Rng.Int(0, WINDOW_HEIGHT - 40);
    ShooterEnemy* shooter = new ShooterEnemy(WINDOW_WIDTH, heightRNG, -150, 0, 10);
    shooter->LoadTexture("croco", 76, 40, 1, false);
    shooter->Init();
    shooter->SetProjectilesVector(m_Projectiles);
    enemies.push_back(shooter);
}