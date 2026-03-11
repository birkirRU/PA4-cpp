#ifndef BOARD_BOARD_H_
#define BOARD_BOARD_H_

#include <array>
#include <iostream>
#include "../entities/player.h"
#include "../entities/enemy.h"
#include "../entities/entity.h"
#include "../card/card.h"

class Board {

    private:
        std::array<int, 3>* board[3];

        // Board looks like 
        // [] [] [] <- next card that enemy is going to play

        // [] [] [] <- active enemy cards
        // [] [] [] <- your active cards
        std::array<int, 3> enemyActiveCards{{-1, -1, -1}};
        std::array<int, 3> enemyPreCards{{-1, -1, -1}};
        std::array<int, 3> playerActiveCards{{-1, -1, -1}};
        

    public:
        void placeCard(entityType et, const int& cardId, const int& pos);
        void removeCard(entityType et, int cardId);
        void printBoard(); 
};
#endif // BOARD_BOARD_H_
