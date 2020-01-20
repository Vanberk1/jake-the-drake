#pragma once

#include <vector>
#include <ctime>
#include "enemy.h"

class EnemySpawner {
private:
    std::vector<Enemy>* m_Enemies;
    int m_SpawnRate;
    int m_Timer;

public:
    EnemySpawner(std::vector<Enemy>* enemies, int spawnRate);
    void Run();
    void SendWave();
};