#ifndef BOARD_BOARD_H_
#define BOARD_BOARD_H_

#include <array>
#include <iostream>
#include "../entities/player.h"
#include "../entities/enemy.h"
#include "../entities/entity.h"
#include "../card/card.h"

class Board {

    public:

        // Board looks like 
        // [] [] [] <- next card that enemy is going to play
        // [] [] [] <- active enemy cards
        // [] [] [] <- your active cards
        
    std::array<CardInstance, 3> enemyActiveCards;
    std::array<CardInstance, 3> enemyPreCards;
    std::array<CardInstance, 3> playerActiveCards;
        

    public:
        void placeCard(entityType et, const CardInstance& card, const int& pos);
        void removeCard(entityType et, int cardId);
        void printBoard(const std::array<CardInstance, 3>& board); 
};
#endif // BOARD_BOARD_H_
