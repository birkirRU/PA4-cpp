#include "inscryption.h"

void Game::startGame() {
    
    std::cout << "-----------------------" << "\n";
    std::cout << "                       " << "\n";
    std::cout << "  Welcome to Inscryption " << "\n";
    std::cout << "                       " << "\n";
    std::cout << "  Press anything to start" << "\n";
    std::cout << "                       " << "\n";

    std::cin.ignore();
    battleManager.battle();
}