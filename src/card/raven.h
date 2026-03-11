#ifndef CARD_RAVEN_H_
#define CARD_RAVEN_H_

#include "card.h"

class Raven : public Card<Raven> {
public:
    Raven(): Card<Raven>(3,1,1, {SigilName::MIGHTY_LEAP}) {};
    void block();
    void attack();
};

#endif // CARD_RAVEN_H_
