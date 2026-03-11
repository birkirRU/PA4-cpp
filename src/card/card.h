#include <../sigil/sigil.h>
#include <vector>

enum struct ActionType {
    BLOCK,
    ATTACK
};

struct CardInstance {

    const int id;
    std::variant<std::monostate, Bullfrog> card;

    CardInstance() : id(-1), card(std::monostate{}) {}

    template<typename CardType>
    CardInstance(const CardType& card) : id(_nextId()), card(card) {}

    
private:
    static int _nextId();
};


template<typename DerivedCardType>
class Card {

public:
    int health;
    int damage;
    const int bloodcost;

    std::vector<SigilName> sigils;

    Card(int h, int a, int b, const std::vector<SigilName>& s) : health(h), damage(a), bloodcost(b), sigils(s) {}

    void action(ActionType actionType);
};