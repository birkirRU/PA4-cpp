#ifndef CARD_CARD_H_
#define CARD_CARD_H_

#include <variant>
#include "../sigil/sigil.h"
#include <vector>
#include "bullfrog.h"
#include "great_white.h"
#include "raven.h"
#include "squirrel.h"
#include "wolf_cup.h"
#include "wolf.h"

enum struct ActionType {
    BLOCK,
    ATTACK
};


template<typename DerivedCardType>
class Card {

public:
    int health;
    int damage;
    const int bloodcost;

    std::vector<SigilName> sigils;

    Card(int h, int a, int b, const std::vector<SigilName>& s) : health(h), damage(a), bloodcost(b), sigils(s) {}

    void action(ActionType actionType);
};
#endif // CARD_CARD_H_
