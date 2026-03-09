#include <../sigil/sigil.h>
#include <vector>

enum struct ActionType {
    BLOCK,
    ATTACK
};


template<typename DerivedCardType>
class Card {
private:
    int _nextId();

public:
    constexpr int id = _nextId();
    int health;
    int damage;
    const int bloodcost;

    std::vector<SigilName> sigils;

    Card(int h, int a, int b, const std::vector& s) : health(h), damage(a), bloodcost(b), sigils(s) {}

    void action(ActionType actionType);
};