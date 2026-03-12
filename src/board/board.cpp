#include "board.h"


void Board::placeCard(entityType et, const CardInstance& card, const int& pos) {
    if (et == entityType::PLAYER) {
        playerActiveCards[pos] = card;
    } else if (et == entityType::ENEMY) {
        enemyActiveCards[pos] = card;
    } else if (et == entityType::ENEMY_PRE_PLACE) {
        enemyPreCards[pos] = card;
    }
};

void Board::removeCard(entityType et, int cardId) {
    std::array<CardInstance, 3> listToCheck;

    if (et == entityType::PLAYER) {
        listToCheck = playerActiveCards;
    } else if (et == entityType::ENEMY) {
        listToCheck = enemyActiveCards;
    } else if (et == entityType::ENEMY_PRE_PLACE) {
        listToCheck = enemyPreCards; 
    }
    for (CardInstance& c : listToCheck) {
        if (c.id == cardId) {
            c = CardInstance();
            break;
        }
    }
}

void Board::printBoard(const std::array<CardInstance, 3>& board) {
    for (const auto& i : board) {
        std::visit([](const auto& a) {
            using T = std::decay_t<decltype(a)>;
            if constexpr (std::is_same_v<T, std::monostate>) {
                std::cout << "[empty] ";
            } else {
                std::cout << "[" << a.name << "] ";
            }
        }, i.card);
    }
    std::cout << std::endl;
}

void Board::printHand(const std::vector<CardInstance>& hand) {
    for (const auto& i : hand) {
        std::visit([](const auto& a) {
            using T = std::decay_t<decltype(a)>;
            if constexpr (std::is_same_v<T, std::monostate>) {
                std::cout << "[empty] ";
            } else {
                std::cout << "[" << a.name << "] ";
            }
        }, i.card);
    }
    std::cout << std::endl;
}