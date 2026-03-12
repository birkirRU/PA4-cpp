#ifndef CARD_BULLFROG_H_
#define CARD_BULLFROG_H_

#include "card.h"

class Bullfrog : public Card<Bullfrog> {
public:
    std::string name = "Bullfrog";
    Bullfrog(): Card (3,1,1, {SigilName::MIGHTY_LEAP}) {};
    void block();
    void attack();
};
#endif // CARD_BULLFROG_H_
