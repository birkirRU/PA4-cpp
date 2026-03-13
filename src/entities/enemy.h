#ifndef ENTITIES_ENEMY_H_
#define ENTITIES_ENEMY_H_

#include "entity.h"
#include "../card/card.h"

class Enemy : public Entity {
public:
    Enemy(int health) ;
    void randomPreRow (std::array<Card*, 3>& enemyPreCards);
private:
     std::vector<Card*> preCards;
};
#endif // ENTITIES_ENEMY_H_
