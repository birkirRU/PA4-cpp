#include "card.h"

class Bullfrog : public Card<Bullfrog> {
public:
    Bullfrog(): Card (3,1,1, {SigilName::MIGHTY_LEAP}) {};
    void block();
    void attack();
};