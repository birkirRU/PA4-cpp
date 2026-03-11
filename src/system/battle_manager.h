#include "entities/player.h"
#include "entities/enemy.h"

class BattleManager {
    private:
        const Player& currentplayer;
        const Enemy& currentenemy;
        const Board& currentboard;

        void startBattle();
        void endBattle();
        void initializeTurn();
        void playTurn(); 
        

    public:
        BattleManager(const Player& player, const Enemy& enemy, const Board& board);
        void battle();
};