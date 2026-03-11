#ifndef DECK_DECK_H_
#define DECK_DECK_H_

#include "../card/card.h"
#include "../card/cardinstance.h"
#include "../card/bullfrog.h"

#include <variant>
#include <vector>
#include <random>
#include <algorithm>


class Deck {
private:
    std::vector<CardInstance> deck;
    int top = 0; // Index of the top card in the deck
public:
    template<typename CardType>
    void addCard(const CardType& cardType) {
        deck.emplace_back(cardType);  // Creates CardInstance with new ID
    }
    void shuffle();
    int drawCard();
};
#endif // DECK_DECK_H_
