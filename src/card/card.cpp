#include "card.h"


template<typename DerivedCardType>
void Card<DerivedCardType>::action(ActionType actionType) {
    switch (actionType) {
        case ActionType::BLOCK:
            static_cast<DerivedCardType*>(this)->block();
            break;
        case ActionType::ATTACK:
            static_cast<DerivedCardType*>(this)->attack();
            break;
        default:
            break;
    }
}


int CardInstance::_nextId() {
    static int count = 1;
    return count++;
}