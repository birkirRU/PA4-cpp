#include "battle_manager.h"


void BattleManager::battle() {
    
    int round = 0;
    initBattle();
    while (!player.isDead() && !enemy.isDead()) {
        initializeTurn(round);
        playTurn();
        round++;
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

void BattleManager::initializeTurn(int round) {

    board.moveEnemyPreCardsToActive();
    enemy.randomPreRow(round, board.enemyPreCards, board.enemyActiveCards);
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
    std::cout << "\n--- Your attacks ---\n";
    board.resolveCombat(entityType::PLAYER);
    std::cout << "Board after your attacks:\n";
    board.printFullBoard();

    std::cout << "\n--- Enemy attacks ---\n";
    board.moveEnemyPreCardsToActive();
    board.resolveCombat(entityType::ENEMY);
    std::cout << "Board after enemy attacks:\n";
    board.printFullBoard();

    board.onTurnEnd();
}
