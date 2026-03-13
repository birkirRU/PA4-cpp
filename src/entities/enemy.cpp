#include "enemy.h"

Enemy::Enemy(int health, int maxHealth) : Entity(health, maxHealth) {
    deckObj.addCard<Bullfrog>();
    deckObj.addCard<Wolf>();
    deckObj.addCard<Raven>();
    deckObj.addCard<GreatWhite>();
    deckObj.addCard<WolfCup>();
}

void Enemy::randomPreRow (int round, std::array<Card*, 3>& enemyPreCards, std::array<Card*, 3>& enemyActiveCards) {
    Card* random_card = deckObj.random_card_max_blood(round + 1);

    if (!random_card) {
        return;
    };

    bool open_slot = false;

    for (int i = 0; i < 3; i++) {
        if (!enemyPreCards[i] && !enemyActiveCards[i]) { 
            open_slot = true; 
            break; }
    }

    if (!open_slot) {
        return;
    };

    while (true) {
        srand(time(nullptr));
        int randomNum = rand() % 3;

        if (!enemyPreCards[randomNum]  && !enemyActiveCards[randomNum]) {
            enemyPreCards[randomNum] = random_card;
            break;
        }

    }

}
