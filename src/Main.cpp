#include "Game.hpp"
#include "State.hpp"
#include "TitleState.hpp"
#include <iostream>
#include <fstream>

int main (int argc, char** argv) {
    Game& jogo = Game::GetInstance();
    State* initState = (State*) (new TitleState());
    jogo.Push(initState);
    jogo.Run();
    return 0;
}