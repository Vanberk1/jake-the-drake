#pragma once

#include <vector>
#include <ctime>
#include "duck.h"
#include "normalEnemy.h"
#include "bombEnemy.h"
#include "util/random.h"

class EnemySpawner {
private:
    Random m_Rng;
    int m_SpawnRate;
    float m_NormalTimer;
    float m_BombTimer;
    Duck* m_Target;
public:
    EnemySpawner(int spawnRate, Duck* target);
    void Run(float deltaTime, std::vector<Enemy*>& enemies);
    void SendWave(std::vector<Enemy*>& enemies);
    void SpawnBomb(std::vector<Enemy*>& enemies);
};