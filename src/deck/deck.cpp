#include "deck.h"

void Deck::shuffle() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(deck.begin(), deck.end(), g);
}
int Deck::drawCard() {
    return deck[top++].id;  // Return the ID of the drawn card and move top index
}