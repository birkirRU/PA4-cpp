#include "entity.h"

class Player: public Entity {
private:
    Deck squirrelDeck;

public:
    void drawCard();
    void drawSquirrel();
    void playCard(Board& board);
    bool sacrifice(Board& board, int bloodCost);
};