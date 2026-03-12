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

bool Player::sacrifice(Board& board, int bloodCost) {
    if (bloodCost <= 0) return true;

    int onBoard = 0;
    for (int s = 0; s < 3; ++s) {
        if (board.getCardAt(entityType::PLAYER, s)) ++onBoard;
    }
    if (onBoard < bloodCost) {
        std::cout << "You need " << bloodCost << " blood but only have " << onBoard
                << " card(s) on your row. Place more cards first." << std::endl;
        return false;
    }

    std::cout << "You need " << bloodCost << " blood. Sacrifice " << bloodCost
            << " card(s) from your row. Enter " << bloodCost << " slot(s) (0, 1, or 2), e.g. 0 1: ";

    std::vector<int> slots;
    for (int i = 0; i < bloodCost; ++i) {
        int slot;
        std::cin >> slot;
        slots.push_back(slot);
    }

    for (int s : slots) {
        Card* card = board.getCardAt(entityType::PLAYER, s);
        if (card) board.removeCard(entityType::PLAYER, card);
    }
    return true;
}