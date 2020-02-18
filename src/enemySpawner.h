#pragma once

#include <vector>
#include <ctime>
#include "duck.h"
#include "normalEnemy.h"
#include "bombEnemy.h"
#include "shooterEnemy.h"
#include "util/random.h"

class EnemySpawner {
private:
    Random m_Rng;
    int m_SpawnRate;
    float m_NormalTimer;
    float m_BombTimer;
    float m_ShooterTimer;
    Duck* m_Target;
    std::vector<Bullet>* m_Projectiles;
public:
    EnemySpawner(int spawnRate, Duck* target, std::vector<Bullet>* projectiles);
    void Run(float deltaTime, std::vector<Enemy*>& enemies);
    void SendWave(std::vector<Enemy*>& enemies);
    void SpawnBomb(std::vector<Enemy*>& enemies);
    void SpawnShooter(std::vector<Enemy*>& enemies);
};