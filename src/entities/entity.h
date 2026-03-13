#ifndef ENTITIES_ENTITY_H_
#define ENTITIES_ENTITY_H_

#include <vector>
#include "../deck/deck.h"

class Board;
class Card;

enum struct entityType {
    PLAYER,
    ENEMY_PRE_PLACE,
    ENEMY
};


class Entity {
    private:
        static int _nextId();
    public:
        std::vector<Card*> hand;
        Deck deckObj;

    public:
        int health;
        int maxHealth;
        int id;

        Entity(int health, int max = -1): health(health), maxHealth(health), id(_nextId()) {
            if (max >= 0) {
                maxHealth = max;
            }
        };

        virtual void shuffleDeck();
        virtual void drawStartingHand();
        virtual void drawCard();
        virtual bool isDead() const; 
};
#endif
