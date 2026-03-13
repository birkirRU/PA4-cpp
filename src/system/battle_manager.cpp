#include "battle_manager.h"


void BattleManager::battle() {
    
    initBattle();
    while (!player.isDead() && !enemy.isDead()) {
        initializeTurn();
        playTurn();
    }

    if (player.isDead()) {
        std::cout << "Enemy wins!" << "\n";
    } else {
        std::cout << "You win!" << "\n";
    }
}

void BattleManager::initBattle() {
    player.shuffleDeck();
    enemy.shuffleDeck();
    player.drawStartingHand();
    player.drawSquirrel();
    enemy.drawStartingHand();
}

void BattleManager::initializeTurn() {

    board.moveEnemyPreCardsToActive();
    enemy.randomPreRow(board.enemyPreCards, board.enemyActiveCards);
    board.printFullBoard();

    if (board.currentTurn > 0) {
        std::string temp;
        std::cout << "Do you want to draw a card from deck or a squirrel?: (s/c): ";
        std::cin >> temp;
        if (temp == "c") {
            player.drawCard();
        } else {
            player.drawSquirrel();
        }
    }

    std::cout << "Here is your hand: " << "\n";
    board.printHand(player.hand);

    while (player.playCard(board)) {
        board.printFullBoard();
        std::cout << "Your hand: " << "\n";
        board.printHand(player.hand);
    }
}

void BattleManager::playTurn() {
    board.resolveCombat(entityType::PLAYER);
    board.resolveCombat(entityType::ENEMY);
    board.onTurnEnd();
}
