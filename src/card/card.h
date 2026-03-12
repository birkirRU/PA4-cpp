#ifndef CARD_CARD_H_
#define CARD_CARD_H_

#include <vector>
#include "../sigil/sigil.h"

enum struct ActionType {
    BLOCK,
    ATTACK
};


template<typename DerivedCardType>
class Card {

public:
    int health;
    int damage;
    int bloodcost;

    std::vector<SigilName> sigils;

    Card(int h, int a, int b, const std::vector<SigilName>& s) : health(h), damage(a), bloodcost(b), sigils(s) {}

    void action(ActionType actionType);
};
#endif // CARD_CARD_H_
