#include "battle_manager.h"


BattleManager::BattleManager(const Player& player, const Enemy& enemy) : currentplayer(player), currentenemy(enemy) {}

void BattleManager::battle() {
    initBattle();
    while (true) {
        
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