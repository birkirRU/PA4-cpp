#include "enemy.h"

Enemy::Enemy(int health) : Entity(health) {
    deckObj.addCard<Bullfrog>();
    deckObj.addCard<Wolf>();
    deckObj.addCard<Raven>();
    deckObj.addCard<GreatWhite>();
    deckObj.addCard<WolfCup>();
}

void Enemy::randomPreRow (std::array<Card*, 3>& enemyPreCards) {
    Card* random_card = deckObj.drawCard();

    bool open_slot = false;

    for (int i = 0; i < 3; i++) {
        if (!enemyPreCards[i]) { 
            open_slot = true; 
            break; }
    }

    if (!open_slot) {
        return;
    };

    while (true) {
        int randomNum = rand() % 3;

        if (!enemyPreCards[randomNum]) {
            enemyPreCards[randomNum] = random_card;
            break;
        }

    }

}
