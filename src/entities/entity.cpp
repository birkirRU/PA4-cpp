#include "entity.h"

int Entity::_nextId() {
    static int idCounter = 1;
    return idCounter++;
}


bool Entity::isDead() const {
    return health <= 0;
}


void Entity::shuffleDeck() {
    deckObj.shuffle();
}

void Entity::drawStartingHand() {
    for (int i = 0; i < 3; i++) {
        hand.push_back(deckObj.drawCard());
    }
}

void Entity::drawCard() {
    Card* c = deckObj.drawCard();
    if (c) hand.push_back(c);
}