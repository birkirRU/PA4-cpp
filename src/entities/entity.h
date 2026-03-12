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
    public:
        std::vector<CardInstance> hand;
        Deck deckObj;

    public:
        int health;
        int id;

        Entity(int health): health(health), id(_nextId()) {};

        virtual void shuffleDeck();
        virtual void drawStartingHand();
        virtual bool isDead() const; 
};
#endif // ENTITIES_ENTITY_H_
