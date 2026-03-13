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
    /** Returns true if a card was placed (continue turn), false if player chose to end turn (0/done) or hand empty. */
    bool playCard(Board& board);
    bool sacrifice(Board& board, int bloodCost);
    /** Same but \a positionCountsAsSacrifice (0-2) is already chosen as one sacrifice (e.g. placing on that square). */
    bool sacrifice(Board& board, int bloodCost, int positionCountsAsSacrifice);
};
#endif // ENTITIES_PLAYER_H_
