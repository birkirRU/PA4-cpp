#include "deck.h"


Card* Deck::drawCard() {
    if (drawPile.empty()) {
        return nullptr;
    }
    Card* card = drawPile.back();
    drawPile.pop_back();
    hand.push_back(card);
    return card;
}

void Deck::discardCard(Card* card) {
    for (auto it = hand.begin(); it != hand.end(); ++it) {
        if (*it == card) {
            hand.erase(it);
            discardPile.push_back(card);
            return;
        }
    }
}

void Deck::shuffle() {
    shuffleDrawPile();
}

void Deck::shuffleDrawPile() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(drawPile.begin(), drawPile.end(), g);
}
