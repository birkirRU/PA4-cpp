#include "sigil/sigil.h"
#include "deck/deck.h"
#include "board/board.h"
#include "entities/player.h"
#include "entities/enemy.h"

class Game {
    public:
        Player player;
        Enemy enemy;
        Board board;
        SigilRegister sigilRegister;

        Game();
        void startGame();
        void endGame();
};