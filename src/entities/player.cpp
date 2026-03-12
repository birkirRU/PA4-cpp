#include "player.h"

Player::Player(int health) : Entity(health) {
    deckObj.addCard<Bullfrog>();
    deckObj.addCard<Wolf>();
    deckObj.addCard<Raven>();
    deckObj.addCard<GreatWhite>();
    deckObj.addCard<WolfCup>();
}

void Player::drawSquirrel() {
    hand.push_back(deckObj.drawCard());
}

void Player::drawCard() {
    hand.push_back(deckObj.drawCard());
}

void Player::playCard(Board& board) {
    if (hand.empty()) {
        std::cout << "Your hand is empty." << std::endl;
        return;
    }
    std::cout << "Place a card? Enter hand number (1-" << hand.size() << ") and position in your row (0, 1, 2), or 0 to skip: ";
    int idx, lane;
    std::cin >> idx;
    if (idx == 0) return;
    std::cin >> lane;
    if (idx < 1 || static_cast<size_t>(idx) > hand.size() || lane < 0 || lane > 2) {
        std::cout << "Invalid input, skipped." << std::endl;
        return;
    }
    Card* chosen = hand[idx - 1];
    board.placeCard(entityType::PLAYER, chosen, lane);
    hand.erase(hand.begin() + (idx - 1));
    std::cout << "Placed " << chosen->name << " in lane " << lane << "." << std::endl;
}