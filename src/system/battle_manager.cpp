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
    board.initializeBoard();
    player.shuffleDeck();
    enemy.shuffleDeck();
    player.drawStartingHand();
}