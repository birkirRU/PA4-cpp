#include "enemy.h"

Enemy::Enemy(int health) : Entity(health) {

    // Initialize
    deck.addCard(Bullfrog());
    // ...
}