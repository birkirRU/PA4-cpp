#include "../card/card.h"
#include "../card/bullfrog.h"

#include <variant>
#include <vector>

class Deck {
private:
    std::vector<CardInstance> deck;
public:
    template<typename CardType>
    void addCard(const CardType& cardType) {
        deck.emplace_back(cardType);  // Creates CardInstance with new ID
    }
};

