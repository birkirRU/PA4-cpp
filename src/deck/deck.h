#ifndef DECK_DECK_H_
#define DECK_DECK_H_

#include "../card/card.h"

#include <vector>
#include <memory>
#include <random>
#include <algorithm>

class Deck {
private:
    std::vector<std::unique_ptr<Card>> cards;
    std::vector<Card*> drawPile;
    std::vector<Card*> hand;
    std::vector<Card*> discardPile;
    
public:
    template<typename CardType>
    void addCard() {
        auto ptr = std::make_unique<CardType>();
        drawPile.push_back(ptr.get());
        cards.push_back(std::move(ptr));
}

    Card* drawCard();
    void discardCard(Card* card);
    void shuffle();
    Card* random_card_max_blood(int max_blood);

    std::vector<Card*>& getHand() { return hand; }
    const std::vector<Card*>& getHand() const { return hand; }
};

#endif
