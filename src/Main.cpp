#include "Game.hpp"
#include <iostream>
#include <fstream>

int main (int argc, char** argv) {
    Game& jogo = Game::GetInstance();
    jogo.Run();
    return 0;
}