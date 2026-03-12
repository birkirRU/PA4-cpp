#ifndef ENTITIES_PLAYER_H_
#define ENTITIES_PLAYER_H_

#include "entity.h"
#include "../card/card.h"
#include "../board/board.h"

class Player: public Entity {
private:
    Deck squirrelDeck;

public:
    Player(int health);
    void drawCard();
    void drawSquirrel();
    bool sacrifice(Board& board, int bloodCost);
};
#endif // ENTITIES_PLAYER_H_
