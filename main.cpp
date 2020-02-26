#include "src/game.h"

bool IsRunning;

int main(int argc, char* argv[]) {
    Game game(WINDOW_WIDTH, WINDOW_HEIGHT);
    game.Init();
    while(IsRunning) {
        game.InputHandler();
        game.Update();
        game.Render();
    }
    game.Destroy(); 
    return 0;
}