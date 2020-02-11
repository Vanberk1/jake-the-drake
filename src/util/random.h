#pragma once

#include <random>
#include <ctime>

class Random {
private:
    std::mt19937 m_Rng;
public:
    Random() 
        : m_Rng(std::time(nullptr)) {
    }

    int Int(int min, int max) {
        return Get<std::uniform_int_distribution<int>>(min, max);
    }

    float Float(float min, float max) {
        return Get<std::uniform_real_distribution<float>>(min, max);
    }
    
    template<typename T>
    T Get(T min, T max) {
        return Get<std::uniform_real_distribution<T>>(min, max);
    }

    template<typename Dist, typename T>
    T Get(T min, T max) {
        Dist dist(min, max);
        return dist(m_Rng);
    }
};