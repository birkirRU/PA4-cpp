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
    enemy.drawStartingHand();
}

void BattleManager::initializeTurn() {

    board.moveEnemyPreCardsToActive();
    enemy.randomPreRow(board.enemyPreCards, board.enemyActiveCards);
    board.printFullBoard();


    // need to find a way to only force draw single squirrel when its you first turn.
    // Player always starts with single squirrel in hand, and 3 random drawn cards


    // this is wrong, you are only allowed to draw either a regular card or a squirrel.
    std::string temp;
    std::cout << "Do you want to draw a card from deck or a squirrel?: (s/c): ";
    std::cin >> temp;

    if (temp == "c") {
        player.drawCard();
    }
   else {
        player.drawSquirrel();
    }

    std::cout << "Here is your hand: " << "\n";
    board.printHand(player.hand);

    player.playCard(board);
}

void BattleManager::playTurn() {

    board.resolveCombat(entityType::PLAYER);
    board.resolveCombat(entityType::ENEMY);
    board.onTurnEnd();
}
