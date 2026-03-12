#include "battle_manager.h"


void BattleManager::battle() {
    
    initBattle();
    while (!player.isDead() && !enemy.isDead()) {
        initializeTurn();
        playTurn();
    }

}

void BattleManager::initBattle() {
    player.shuffleDeck();
    enemy.shuffleDeck();
    player.drawStartingHand();
}

void BattleManager::initializeTurn() {

    board.printFullBoard();

    std::string temp;
    std::cout << "Do you want to draw a card?: (yes/no) ";
    std::cin >> temp;

    if (temp == "yes") {
        player.drawCard();
    }
    std::cout << "Do you want to draw a squirrel?: (yes/no) ";
    std::cin >> temp;

    if (temp == "yes") {
        player.drawSquirrel();
    }

     std::cout << "Here is your hand: ";
     board.printHand(player.hand);


}

void BattleManager::playTurn() {
    player.shuffleDeck();
    enemy.shuffleDeck();
    player.drawStartingHand();
}

