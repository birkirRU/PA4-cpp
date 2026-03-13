#include "player.h"
#include <string>
#include <cctype>

Player::Player(int health, int maxHealth) : Entity(health, maxHealth) {
    deckObj.addCard<Bullfrog>();
    deckObj.addCard<Wolf>();
    deckObj.addCard<Raven>();
    deckObj.addCard<GreatWhite>();
    deckObj.addCard<WolfCup>();
}

void Player::drawSquirrel() {
    hand.push_back(new Squirrel());
}

void Player::drawCard() {
    Card* c = deckObj.drawCard();
    if (c) {
        hand.push_back(c);
    }
}

static std::string toLower(const std::string& s) {
    std::string r = s;
    for (char& c : r) {
        c = std::tolower(c);
    }
    return r;
}

static bool parsePlaceInput(const std::string& first, const std::string& second, size_t handSize, int& outIdx, int& outPos) {
    int idx = 0;
    for (char c : first) {
        if (c < '0' || c > '9') {
            return false;
        }
        idx = idx * 10 + (c - '0');
    }
    if (idx < 1 || static_cast<size_t>(idx) > handSize) {
        return false;
    }
    if (second.size() != 1 || second[0] < '0' || second[0] > '2') {
        return false;
    }
    outIdx = idx;
    outPos = second[0] - '0';
    return true;
}

static bool requireSacrificeForPlace(Board& board, Player& player, Card* chosen, int pos) {
    Card* atPos = board.getCardAt(entityType::PLAYER, pos);
    if (atPos) {
        if (chosen->bloodCost == 0) {
            std::cout << "Replacing " << atPos->name << " with " << chosen->name << "." << "\n";
            board.removeCard(entityType::PLAYER, atPos);
            return true;
        }
        std::cout << chosen->name << " costs " << chosen->bloodCost << " blood. The card in position " << pos << " counts as 1." << "\n";
        return player.sacrifice(board, chosen->bloodCost, pos);
    }
    if (chosen->bloodCost > 0) {
        std::cout << chosen->name << " costs " << chosen->bloodCost << " blood. You must sacrifice that many cards from your row first." << "\n";
        return player.sacrifice(board, chosen->bloodCost);
    }
    return true;
}

bool Player::playCard(Board& board) {
    if (hand.empty()) {
        std::cout << "Your hand is empty." << "\n";
        return false;
    }
    std::cout << "Place a card: hand number (1-" << hand.size() << ") and position (0, 1, or 2). Type done to end your turn: ";
    std::string first, second;
    std::cin >> first;
    if (toLower(first) == "done") {
        std::cout << "Turn ended." << "\n";
        return false;
    }
    std::cin >> second;
    int idx, pos;
    if (!parsePlaceInput(first, second, hand.size(), idx, pos)) {
        std::cout << "Invalid input." << "\n";
        return true;
    }
    Card* chosen = hand[idx - 1];
    if (!requireSacrificeForPlace(board, *this, chosen, pos)) {
        std::cout << "Placement cancelled." << "\n";
        return true;
    }
    board.placeCard(entityType::PLAYER, chosen, pos);
    hand.erase(hand.begin() + (idx - 1));
    std::cout << "Placed " << chosen->name << " in position " << pos << "." << "\n";
    return true;
}

bool Player::sacrifice(Board& board, int bloodCost) {
    return sacrifice(board, bloodCost, -1);
}

static int countPlayerCards(Board& board) {
    int n = 0;
    for (int s = 0; s < 3; ++s) {
        if (board.getCardAt(entityType::PLAYER, s)) {
            ++n;
        }
    }
    return n;
}

static void removeCardsAt(Board& board, const std::vector<int>& positions) {
    for (int p : positions) {
        Card* card = board.getCardAt(entityType::PLAYER, p);
        if (card) {
            board.removeCard(entityType::PLAYER, card);
        }
    }
}

static bool readSacrificePositions(Board& board, int needFromUser, int positionCountsAsSacrifice, std::vector<int>& positions) {
    if (positionCountsAsSacrifice >= 0 && positionCountsAsSacrifice <= 2) {
        positions.push_back(positionCountsAsSacrifice);
    }
    for (int i = 0; i < needFromUser; ++i) {
        int pos;
        std::cin >> pos;
        if (pos < 0 || pos > 2) {
            std::cout << "Invalid position " << pos << ". Use 0, 1, or 2." << "\n";
            return false;
        }
        if (!board.getCardAt(entityType::PLAYER, pos)) {
            std::cout << "Position " << pos << " has no card to sacrifice." << "\n";
            return false;
        }
        if (positionCountsAsSacrifice >= 0 && pos == positionCountsAsSacrifice) {
            std::cout << "Position " << pos << " is already counted. Pick " << needFromUser << " other position(s)." << "\n";
            return false;
        }
        positions.push_back(pos);
    }
    for (size_t i = 0; i < positions.size(); ++i) {
        for (size_t j = i + 1; j < positions.size(); ++j) {
            if (positions[i] == positions[j]) {
                std::cout << "Each sacrifice must be a different position. You entered position " << positions[i] << " more than once." << "\n";
                return false;
            }
        }
    }
    return true;
}

bool Player::sacrifice(Board& board, int bloodCost, int positionCountsAsSacrifice) {
    if (bloodCost <= 0) {
        return true;
    }
    int onBoard = countPlayerCards(board);
    int needFromUser = bloodCost;
    if (positionCountsAsSacrifice >= 0 && positionCountsAsSacrifice <= 2 &&
            board.getCardAt(entityType::PLAYER, positionCountsAsSacrifice)) {
        needFromUser = bloodCost - 1;
    }
    if (onBoard < bloodCost) {
        std::cout << "You need " << bloodCost << " blood but only have " << onBoard << " card(s) on your row. Place more cards first." << "\n";
        return false;
    }
    if (needFromUser == 0) {
        std::vector<int> one = {positionCountsAsSacrifice};
        removeCardsAt(board, one);
        std::cout << "Sacrificed 1 card (position " << positionCountsAsSacrifice << ")." << "\n";
        return true;
    }
    std::cout << "Sacrifice " << bloodCost << " card(s). ";
    if (needFromUser < bloodCost) {
        std::cout << "Position " << positionCountsAsSacrifice << " counts as 1. ";
    }
    std::cout << "Enter " << needFromUser << " more position(s) (0, 1, or 2), e.g. ";
    if (needFromUser == 1) {
        std::cout << "0";
    } else if (needFromUser == 2) {
        std::cout << "0 1";
    } else {
        std::cout << "0 1 2";
    }
    std::cout << ": ";
    std::vector<int> positions;
    if (!readSacrificePositions(board, needFromUser, positionCountsAsSacrifice, positions)) {
        return false;
    }
    removeCardsAt(board, positions);
    std::cout << "Sacrificed " << bloodCost << " card(s)." << "\n";
    return true;
}
