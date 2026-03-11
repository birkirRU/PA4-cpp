#include "battle_manager.h"


BattleManager::BattleManager(const Player& player, const Enemy& enemy, const Board& board) : currentplayer(player), currentenemy(enemy), currentboard(board) {}

void BattleManager::battle() {
    startBattle();
    while (true) {
        
        initializeTurn();
        playTurn();
    }
    endBattle();
}

void BattleManager::startBattle() {
    // initialize battle state, shuffle decks, draw starting hands, etc.


}