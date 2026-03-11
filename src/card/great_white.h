#ifndef CARD_GREAT_WHITE_H_
#define CARD_GREAT_WHITE_H_

#include "card.h"

class GreatWhite : public Card<GreatWhite> {
public:
    GreatWhite(): Card<GreatWhite>(3,1,1, {SigilName::MIGHTY_LEAP}) {};
    void block();
    void attack();
};

#endif // CARD_GREAT_WHITE_H_
