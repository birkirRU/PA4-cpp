#ifndef INSCRYPTION_H_
#define INSCRYPTION_H_

#include "sigil/sigil.h"
#include "deck/deck.h"
#include "board/board.h"
#include "entities/player.h"
#include "entities/enemy.h"
#include "system/battle_manager.h"

class Game {
    public:
        Player player;
        Enemy enemy;
        Board board;
        SigilRegister sigilRegister;
        BattleManager battleManager;

        Game() 
            : player(5),
              enemy(5),
              board(),
              sigilRegister(),
              battleManager(player, enemy, board) {}
              
        void startGame();
        void endGame();
};
#endif // INSCRYPTION_H_
