#ifndef CARD_INSTANCE_H_
#define CARD_INSTANCE_H_

#include <variant>
#include "bullfrog.h"
#include "great_white.h"
#include "raven.h"
#include "squirrel.h"
#include "wolf.h"
#include "wolf_cup.h"


struct CardInstance {

    int id;
    std::variant<std::monostate, Bullfrog, Wolf, Raven, GreatWhite, Squirrel, WolfCup> card;

    CardInstance() : id(-1), card(std::monostate{}) {}

    template<typename CardType>
    CardInstance(const CardType& card) : id(_nextId()), card(card) {}

    
private:
    static int _nextId();
};

#endif