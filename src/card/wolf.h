#ifndef CARD_WOLF_H_
#define CARD_WOLF_H_

#include "card.h" 

class Wolf : public Card<Wolf> {
public:
    Wolf(): Card<Wolf>(3,1,1, {SigilName::MIGHTY_LEAP}) {};
    void block();
    void attack();
};


#endif // CARD_WOLF_H_
