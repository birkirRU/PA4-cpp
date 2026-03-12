#include "battle_manager.h"


void BattleManager::battle() {
    
    initBattle();
    while (!player.isDead() && !enemy.isDead()) {
        initializeTurn();
        playTurn();
    }

    if (player.isDead()) {
        std::cout << "Enemy wins!" << std::endl;
    } else {
        std::cout << "You win!" << std::endl;
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

    player.playCard(board);
}

void BattleManager::playTurn() {
    board.resolveCombat(entityType::PLAYER);
    board.resolveCombat(entityType::ENEMY);
    board.onTurnEnd();
}
