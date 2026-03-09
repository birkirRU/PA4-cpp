#include <vector>
#include <iostream>
#include "card.h"

class Board {

    private:
        std::vector<int> cardsOnBoard;

    public:
        void placeCard();
        void removeCard(int cardId);
        void printBoard(); 

};