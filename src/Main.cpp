#include "Game.hpp"
#include <iostream>
int main (int argc, char** argv) {
    std::cout<<"b\n\n";
    Game& jogo = Game::GetInstance();
    jogo.Run();
    return 0;
}