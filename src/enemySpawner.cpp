#include "enemySpawner.h"

EnemySpawner::EnemySpawner(std::vector<Enemy>* enemies, int spawnRate) 
    : m_Enemies(enemies), m_SpawnRate(spawnRate), m_Timer(0) {

}

void EnemySpawner::Run() {
    if(m_Timer < m_SpawnRate) {
        m_Timer++;
    }
    if(m_Timer >= m_SpawnRate) {
        SendWave();
        m_Timer = 0;
    }
}

void EnemySpawner::SendWave() {
    int heightRNG = rand() % WINDOW_HEIGHT;
    int xOffSet = WINDOW_WIDTH;
    int delay = 100;
    int vel = 150;
    int waveLength = 3;
    for(int i = 0; i < 5; ++i) {
        Enemy newEnemy(xOffSet + i * delay, heightRNG, -vel, 0);   
        newEnemy.LoadTexture("croco", 76, 40, 1, false);
        newEnemy.Init();
        m_Enemies->emplace_back(newEnemy);
    }  
}