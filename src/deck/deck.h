#include "../card/card.h"
#include "../card/bullfrog.h"

#include <variant>
#include <vector>

class Deck {
private:
    using anyCard = std::variant<
                        std::monostate, Bullfrog 
                        >;
    std::vector<anyCard> deck = {};
public:
    void addCard(anyCard card);
};