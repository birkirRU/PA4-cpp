#include "inscryption.h"

void Game::startGame() {
    battleManager.battle();
    
    std::cout << "-----------------------" << std::endl;
    std::cout << "                       " << std::endl;
    std::cout << "  Welcome to the game  " << std::endl;
    std::cout << "                       " << std::endl;
    std::cout << "  Press anything to start" << std::endl;
}