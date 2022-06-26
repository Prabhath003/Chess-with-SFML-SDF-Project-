#include <iostream>
#include <Game.hpp>

int main() 
{
    std::cout << "Game Started!" << std::endl;
    Engine::Game game;

    game.run();

    return 0;
}