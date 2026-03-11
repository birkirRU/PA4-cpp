#ifndef SYSTEM_BATTLE_MANAGER_H_
#define SYSTEM_BATTLE_MANAGER_H_

#include "../entities/player.h"
#include "../entities/enemy.h"
#include "../board/board.h"

class BattleManager {
    private:
        const Player& currentplayer;
        const Enemy& currentenemy;
        const Board& board;

        void startBattle();
        void endBattle();
        void initializeTurn();
        void playTurn(); 
        

    public:
        BattleManager(const Player& player, const Enemy& enemy);
        void battle();
};
#endif // SYSTEM_BATTLE_MANAGER_H_
