#include "player.h"


Player::Player(int health) : Entity(health) {
    
    // Initialize decks
    deck.addCard(Bullfrog());
    // ...
    for (int i = 0; i < 10; i++) {
        // squirrelDeck.addCard(Squirrel());
    }

}
