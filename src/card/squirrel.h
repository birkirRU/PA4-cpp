#ifndef CARD_SQUIRREL_H_
#define CARD_SQUIRREL_H_

#include "card.h"

class Squirrel : public Card<Squirrel> {
public:
    Squirrel(): Card<Squirrel>(3,1,1, {SigilName::MIGHTY_LEAP}) {};
    void block();
    void attack();
};


#endif // CARD_SQUIRREL_H_
