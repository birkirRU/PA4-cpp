#ifndef CARD_WOLF_CUP_H_
#define CARD_WOLF_CUP_H_

#include "card.h"

class WolfCup : public Card<WolfCup> {
public:
    WolfCup(): Card<WolfCup>(3,1,1, {SigilName::MIGHTY_LEAP}) {};
    void block();
    void attack();
};


#endif // CARD_WOLF_CUP_H_
