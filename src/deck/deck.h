#include "../card/card.h"
#include "../card/bullfrog.h"

#include <variant>
#include <array>

class Deck {
private:
    using anyCard = std::variant<
                                std::monostate,
                                Bullfrog
                                >;
    std::array<anyCard, 10> deck = {};
};

