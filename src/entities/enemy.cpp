#include "enemy.h"

Enemy::Enemy(int health) : Entity(health) {

    // Initialize
    deckObj.addCard(Bullfrog());
    // ...
}