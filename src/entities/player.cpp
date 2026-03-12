#include "player.h"


Player::Player(int health) : Entity(health) {
    
    deckObj.addCard(Bullfrog());
    deckObj.addCard(Wolf());
    deckObj.addCard(Raven());
    deckObj.addCard(GreatWhite());
    deckObj.addCard(WolfCup());

}

void Player::drawSquirrel() {
    hand.push_back(Squirrel());
}

void Player::drawCard() {
    hand.push_back(deckObj.drawCard());
}



