#include "board.h"

void Board::initializeBoard() {
    for (int i = 0; i < 3; i++) {
        enemyActiveCards[i] = -1;
        enemyPreCards[i] = -1;
        playerActiveCards[i] = -1;
    }
}

void Board::placeCard(entityType et, const int& cardId, const int& pos) {
    if (et == entityType::PLAYER) {
        playerActiveCards[pos] = cardId;
    } else if (et == entityType::ENEMY) {
        enemyActiveCards[pos] = cardId;
    } else if (et == entityType::ENEMY_PRE_PLACE) {
        enemyPreCards[pos] = cardId;
    }
};

void Board::removeCard(entityType et, int cardId) {
    std::array<int, 3> listToCheck;

    if (et == entityType::PLAYER) {
        listToCheck = playerActiveCards;
    } else if (et == entityType::ENEMY) {
        listToCheck = enemyActiveCards;
    } else if (et == entityType::ENEMY_PRE_PLACE) {
        listToCheck = enemyPreCards; 
    }
    for (int& cid : listToCheck) {
        if (cid == cardId) {
            cid = -1;
            break;
        }
    }
}

void Board::printBoard() {
    std::cout << "Enemy next: ";
    std::cout << "[" << enemyPreCards[0] << "] " << "[" << enemyPreCards[1] << "] " << "[" << enemyPreCards[2] << "] " << std::endl;
    std::cout << "Enemy Current: ";
    std::cout << "[" << enemyActiveCards[0] << "] " << "[" << enemyActiveCards[1] << "] " << "[" << enemyActiveCards[2] << "] " << std::endl;
    std::cout << "Player: ";
    std::cout << "[" << playerActiveCards[0] << "] " << "[" << playerActiveCards[1] << "] " << "[" << playerActiveCards[2] << "] " << std::endl;
};