#include "player.h"
#include <string>
#include <cctype>

Player::Player(int health) : Entity(health) {
    deckObj.addCard<Bullfrog>();
    deckObj.addCard<Wolf>();
    deckObj.addCard<Raven>();
    deckObj.addCard<GreatWhite>();
    deckObj.addCard<WolfCup>();
}

void Player::drawSquirrel() {
    // THIS NEEDS TO BE CHANGED, we need to draw from squirrel deck
    // Or genereate a squirrel card instance, and only allow up to e.g. 10 cards
    // Probably need a specific squirrel deck of unuiqe instances of squirrels card to draw from.
    // Squirrel cards are player specific
     hand.push_back(new Squirrel());
}

void Player::drawCard() {
    hand.push_back(deckObj.drawCard());
}

static std::string toLower(const std::string& s) {
    std::string r = s;
    for (char& c : r) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    return r;
}

bool Player::playCard(Board& board) {
    if (hand.empty()) {
        std::cout << "Your hand is empty." << '\n';
        return false;
    }
    std::cout << "Place a card: hand number (1-" << hand.size() << ") and position (0, 1, or 2). Type done to end your turn: ";
    std::string first;
    std::cin >> first;
    if (toLower(first) == "done") {
        std::cout << "Turn ended." << '\n';
        return false;
    }
    int idx = 0;
    try {
        idx = std::stoi(first);
    } catch (...) {
        std::cout << "Invalid input." << '\n';
        return true;
    }
    int pos;
    std::cin >> pos;
    if (idx < 1 || static_cast<size_t>(idx) > hand.size() || pos < 0 || pos > 2) {
        std::cout << "Invalid input." << '\n';
        return true;
    }
    Card* chosen = hand[idx - 1];
    if (!chosen) {
        std::cout << "Invalid card." << '\n';
        return true;
    }

    if (board.getCardAt(entityType::PLAYER, pos)) {
        std::cout << "Position " << pos << " is already occupied. Pick an empty position (0, 1, or 2)." << '\n';
        return true;
    }

    if (chosen->bloodCost > 0) {
        std::cout << chosen->name << " costs " << chosen->bloodCost << " blood. You must sacrifice that many cards from your row first." << '\n';
        if (!sacrifice(board, chosen->bloodCost)) {
            std::cout << "Placement cancelled." << '\n';
            return true;
        }
    }

    board.placeCard(entityType::PLAYER, chosen, pos);
    hand.erase(hand.begin() + (idx - 1));
    std::cout << "Placed " << chosen->name << " in position " << pos << "." << '\n';
    return true;
}

bool Player::sacrifice(Board& board, int bloodCost) {
    if (bloodCost <= 0) return true;

    int onBoard = 0;
    for (int s = 0; s < 3; ++s) {
        if (board.getCardAt(entityType::PLAYER, s)) ++onBoard;
    }
    if (onBoard < bloodCost) {
        std::cout << "You need " << bloodCost << " blood but only have " << onBoard
                << " card(s) on your row. Place more cards first." << '\n';
        return false;
    }

    std::cout << "Sacrifice " << bloodCost << " card(s). Enter " << bloodCost
            << " position(s) (0, 1, or 2), one per card, e.g. ";
    if (bloodCost == 1) std::cout << "0";
    else if (bloodCost == 2) std::cout << "0 1";
    else std::cout << "0 1 2";
    std::cout << ": ";

    std::vector<int> positions;
    for (int i = 0; i < bloodCost; ++i) {
        int pos;
        std::cin >> pos;
        if (pos < 0 || pos > 2) {
            std::cout << "Invalid position " << pos << ". Use 0, 1, or 2." << '\n';
            return false;
        }
        if (!board.getCardAt(entityType::PLAYER, pos)) {
            std::cout << "Position " << pos << " has no card to sacrifice." << '\n';
            return false;
        }
        positions.push_back(pos);
    }

    for (int i = 0; i < static_cast<int>(positions.size()); ++i) {
        for (int j = i + 1; j < static_cast<int>(positions.size()); ++j) {
            if (positions[i] == positions[j]) {
                std::cout << "Each sacrifice must be a different position. You entered position " << positions[i] << " more than once." << '\n';
                return false;
            }
        }
    }

    for (int pos : positions) {
        Card* card = board.getCardAt(entityType::PLAYER, pos);
        if (card) board.removeCard(entityType::PLAYER, card);
    }
    std::cout << "Sacrificed " << bloodCost << " card(s)." << '\n';
    return true;
}