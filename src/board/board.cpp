#include "board.h"


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