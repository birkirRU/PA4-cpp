#include "deck.h"


Card* Deck::drawCard() {
    if (drawPile.empty() && !discardPile.empty()) {
        for (Card* c : discardPile) {
            drawPile.push_back(c);
        }
        discardPile.clear();
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(drawPile.begin(), drawPile.end(), g);
    }
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
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(drawPile.begin(), drawPile.end(), g);
}

Card* Deck::random_card_max_blood (int max_blood) {
    std::vector<Card*> temp;
    for (int i = 0; i < (int)drawPile.size(); i++) {
        if (drawPile[i]->bloodCost <= max_blood) {
            temp.push_back(drawPile[i]);
        }
    }

    if (temp.empty()) {
        return nullptr;
    }
    srand(time(nullptr));
    int pick = rand() % temp.size();
    return temp[pick];
}
