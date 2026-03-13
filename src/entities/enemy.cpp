#include "enemy.h"

Enemy::Enemy(int health, int maxHealth) : Entity(health, maxHealth) {
    deckObj.addCard<Bullfrog>();
    deckObj.addCard<Bullfrog>();
    deckObj.addCard<Bullfrog>();
    deckObj.addCard<Raven>();
    deckObj.addCard<Raven>();
    deckObj.addCard<Raven>();
    deckObj.addCard<Wolf>();
    deckObj.addCard<WolfCup>();
    deckObj.addCard<WolfCup>();
    deckObj.addCard<GreatWhite>();
    deckObj.addCard<GreatWhite>();
}

void Enemy::randomPreRow (int round, std::array<Card*, 3>& enemyPreCards, std::array<Card*, 3>& enemyActiveCards) {
    Card* random_card = deckObj.random_card_max_blood(round + 1);

    if (!random_card) {
        return;
    }

    std::vector<int> empty_slots;
    for (int i = 0; i < 3; i++) {
        if (!enemyPreCards[i] && !enemyActiveCards[i]) {
            empty_slots.push_back(i);
        }
    }

    if (empty_slots.empty()) {
        return;
    }

    int idx = empty_slots[rand() % empty_slots.size()];
    enemyPreCards[idx] = random_card;
}
