#include "enemySpawner.h"

EnemySpawner::EnemySpawner(int spawnRate, Duck* target, std::vector<Bullet>* projectiles)
    : m_SpawnRate(spawnRate), m_NormalTimer(0.0f), m_BombTimer(10.0f), m_Target(target)
    , m_Projectiles(projectiles), m_ShooterTimer(10.0f) {

}

void EnemySpawner::Run(float deltaTime, std::vector<Enemy*>& enemies) {
    m_ShooterTimer += deltaTime;

    // std::cout << "Normal timer: " << m_NormalTimer << std::endl;
    // std::cout << "Bomb timer: " << m_BombTimer << std::endl;

    if(m_ShooterTimer >= m_SpawnRate / 2.0f) {
        SendWave(enemies);
        SpawnShooter(enemies);
        SpawnBomb(enemies);
        SpawnObstacle(enemies);
        m_ShooterTimer = 0;
    }
}

void EnemySpawner::SpawnObstacle(std::vector<Enemy*>& enemies) {
    int heightRNG = m_Rng.Int(120, WINDOW_HEIGHT - 120);
    NormalEnemy* obstacle = new NormalEnemy(WINDOW_WIDTH, heightRNG, -70, 0, 10);
    obstacle->SetHealth(20);
    obstacle->LoadTexture("lilypad", 16, 16, SPRITE_SCALE, true);
    obstacle->AddAnimation("idle", 3, 200, 0);
    obstacle->SetAnimation("idle");
    obstacle->Init();
    enemies.push_back(obstacle);
}

void EnemySpawner::SendWave(std::vector<Enemy*>& enemies) {
    int heightRNG = m_Rng.Int(100, WINDOW_HEIGHT - 100);
    int xOffSet = WINDOW_WIDTH;
    int delay = 100;
    int vel = 150;
    int waveLength = 3;
    for(int i = 0; i < 1; ++i) {
        NormalEnemy* newEnemy = new NormalEnemy(xOffSet + i * delay, heightRNG, -vel, 0, 1);   
        newEnemy->SetHealth(30);
        newEnemy->LoadTexture("normal-enemy", 32, 16, SPRITE_SCALE, true);
        newEnemy->AddAnimation("idle", 3, 200, 0);
        newEnemy->SetAnimation("idle");
        newEnemy->Init();
        enemies.push_back(newEnemy);
    } 
}

void EnemySpawner::SpawnBomb(std::vector<Enemy*>& enemies) { 
    int heightRNG = m_Rng.Int(120, WINDOW_HEIGHT - 120);
    BombEnemy* bomb = new BombEnemy(WINDOW_WIDTH, heightRNG, -150, 0, 10);
    bomb->SetHealth(30);
    bomb->LoadTexture("bomb-enemy", 32, 21, SPRITE_SCALE, true);
    bomb->AddAnimation("idle", 3, 200, 0);
    bomb->AddAnimation("explode", 3, 80, 0);
    bomb->SetAnimation("idle");
    bomb->Init();
    bomb->SetTarget(m_Target);
    enemies.push_back(bomb);
}

void EnemySpawner::SpawnShooter(std::vector<Enemy*>& enemies) {
    int heightRNG = m_Rng.Int(60, WINDOW_HEIGHT - 60);
    ShooterEnemy* shooter = new ShooterEnemy(WINDOW_WIDTH, heightRNG, -100, 0, 10);
    shooter->SetHealth(30);
    shooter->LoadTexture("normal-enemy", 32, 16, SPRITE_SCALE, true);
    shooter->AddAnimation("idle", 3, 200, 0);
    shooter->SetAnimation("idle");
    shooter->Init();
    shooter->SetProjectilesVector(m_Projectiles);
    shooter->SetTarget(m_Target);
    enemies.push_back(shooter);
}