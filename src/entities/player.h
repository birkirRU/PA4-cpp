#ifndef ENTITIES_PLAYER_H_
#define ENTITIES_PLAYER_H_

#include "entity.h"
#include "../card/card.h"
#include "../board/board.h"

class Player: public Entity {
private:
    Deck squirrelDeck;

public:
    Player(int health, int maxHealth = -1);
    void drawCard();
    void drawSquirrel();
    bool playCard(Board& board);
    bool sacrifice(Board& board, int bloodCost);
    bool sacrifice(Board& board, int bloodCost, int positionCountsAsSacrifice);
};
#endif
