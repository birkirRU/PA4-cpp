#ifndef ENTITIES_ENTITY_H_
#define ENTITIES_ENTITY_H_

#include <vector>
#include "../deck/deck.h"

class Board;

enum struct entityType {
    PLAYER,
    ENEMY_PRE_PLACE,
    ENEMY
};


class Entity {
    private:
        static int _nextId();
    protected:
        std::vector<int> hand;
        Deck deck;

    public:
        int health;
        int id;

        Entity(int health): health(health), id(_nextId()) {};
        virtual void playCard(Board& board);
        virtual void attack();
        virtual void block();

        virtual void shuffleDeck();
        virtual void drawStartingHand();
};
#endif // ENTITIES_ENTITY_H_
