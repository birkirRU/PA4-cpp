#ifndef CARD_CARD_H_
#define CARD_CARD_H_

#include <string>
#include <vector>
#include "../sigil/sigil.h"

class Card {
public:
    std::string name;
    int health;
    int damage;
    int bloodCost;
    std::vector<SigilName> sigils;
    bool isBase;

    Card(const std::string& name, int health, int damage, int bloodCost,
         const std::vector<SigilName>& sigils, bool isBase = false);
    virtual ~Card() = default;
};

class Wolf : public Card {
public:
    Wolf() : Card("Wolf", 3, 2, 2, {SigilName::MIGHTY_LEAP}) {}
};

class Raven : public Card {
public:
    Raven() : Card("Raven", 2, 1, 1, {SigilName::AIRBORNE}) {}
};

class Bullfrog : public Card {
public:
    Bullfrog() : Card("Bullfrog", 3, 1, 1, {SigilName::MIGHTY_LEAP}) {}
};

class GreatWhite : public Card {
public:
    GreatWhite() : Card("GreatWhite", 2, 4, 3, {SigilName::WATERBORNE}) {}
};

class Squirrel : public Card {
public:
    Squirrel() : Card("Squirrel", 1, 0, 0, {}) {}
};

class WolfCup : public Card {
public:
    WolfCup() : Card("WolfCup", 1, 1, 1, {SigilName::FLEDGING}, true) {}
};

#endif