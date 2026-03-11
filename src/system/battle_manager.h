#ifndef SYSTEM_BATTLE_MANAGER_H_
#define SYSTEM_BATTLE_MANAGER_H_

#include "../entities/player.h"
#include "../entities/enemy.h"
#include "../board/board.h"

class BattleManager {
    private:
        Player& player;
        Enemy& enemy;
        Board& board;

        void initBattle();
        void endBattle();
        void initializeTurn();
        void playTurn(); 
        

    public:
        BattleManager(Player& player, Enemy& enemy, Board& board) :
            player(player), enemy(enemy), board(board) {}
        void battle();
};
#endif // SYSTEM_BATTLE_MANAGER_H_
