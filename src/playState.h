#pragma once

#include <iostream>
#include "gameState.h"

class PlayState: public GameState {
public:
    void OnEnter() override {
        std::cout << "Enter Play State" << std::endl;
    };

    void OnExit() override {
        std::cout << "Exit Play State" << std::endl;
    };

    void Update(float deltaTime) override {
    };
};