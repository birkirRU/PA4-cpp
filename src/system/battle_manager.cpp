#include "battle_manager.h"


void BattleManager::battle() {
    
    initBattle();
    while (!player.isDead() && !enemy.isDead()) {
        initializeTurn();
        playTurn();
    }
    endBattle();
}

void BattleManager::initBattle() {
    player.shuffleDeck();
    enemy.shuffleDeck();
    player.drawStartingHand();
}

void BattleManager::initializeTurn() {
    board.printBoard();
    std::string temp;
    std::cout << "Do you want to draw a card?: (yes/no) "
    std::cin >> temp;

    if (temp == "yes") {
        player.drawCard();
    }
    std::cout << "Do you want to draw a squirrel?: (yes/no) "
    std::cin >> temp;

    if (temp == "yes") {
        player.drawSquirrel();
    }
}

void BattleManager::playTurn() {
    player.shuffleDeck();
    enemy.shuffleDeck();
    player.drawStartingHand();
}

