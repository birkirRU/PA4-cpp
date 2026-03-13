#ifndef ENTITIES_ENEMY_H_
#define ENTITIES_ENEMY_H_

#include "entity.h"
#include "../card/card.h"

class Enemy : public Entity {
public:
    Enemy(int health, int maxHealth = -1);
    void randomPreRow (int round, std::array<Card*, 3>& enemyPreCards, std::array<Card*, 3>& enemyActiveCards);
private:
     std::vector<Card*> preCards;
};
#endif
