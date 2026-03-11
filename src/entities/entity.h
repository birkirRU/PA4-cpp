#include "../deck/deck.h"

enum struct entityType {
    PLAYER,
    ENEMY_PRE_PLACE,
    ENEMY
};


class Entity {
    private:
        static int _nextId();
        std::vector<int> hand;
        Deck deck;
        

    public:
        int health;
        int id;

        Entity() : health(0), id(_nextId()) {};
        void attack();
        void block();
};