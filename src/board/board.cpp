#include "board.h"
#include "../entities/player.h"
#include "../entities/enemy.h"
#include "../sigil/sigil.h"
#include "../deck/deck.h"

static std::string sigilToShort(SigilName s) {
    switch (s) {
        case SigilName::AIRBORNE:    
            return "AB";
        case SigilName::MIGHTY_LEAP: 
            return "ML";
        case SigilName::WATERBORNE:  
            return "WB";
        case SigilName::FLEDGING:    
            return "FL";
        default:                     
            return "-";
    }
}

static std::string formatSigils(const std::vector<SigilName>& sigils) {
    if (sigils.empty()) return "-";

    std::string result;
    for (size_t i = 0; i < sigils.size(); ++i) {
        if (i > 0) result += ",";
        result += sigilToShort(sigils[i]);
    }
    return result;
}

static std::string formatCard(const Card* c) {
    if (!c) return "[empty]";
    // Format: [Wolf 3/2 C:2 S:ML] <- Format now, we can change this later if we have sth thatrs better
    std::string s = "[";
    s += c->name;
    s += " ";
    s += std::to_string(c->health);
    s += "/";
    s += std::to_string(c->damage);
    s += " C:";
    s += std::to_string(c->bloodCost);
    s += " S:";
    s += formatSigils(c->sigils);
    s += "]";
    return s;
}

Board::Board() : player(nullptr), enemy(nullptr), playerDeck(nullptr), enemyDeck(nullptr), currentTurn(0) {
    playerActiveCards = {nullptr, nullptr, nullptr};
    enemyActiveCards = {nullptr, nullptr, nullptr};
    enemyPreCards = {nullptr, nullptr, nullptr};
}

void Board::placeCard(entityType et, Card* card, int pos) {
    if (pos < 0 || pos >= 3) return;
    
    if (et == entityType::PLAYER) {
        playerActiveCards[pos] = card;
    } else if (et == entityType::ENEMY) {
        enemyActiveCards[pos] = card;
    } else if (et == entityType::ENEMY_PRE_PLACE) {
        enemyPreCards[pos] = card;
    }
}

void Board::removeCard(entityType et, Card* card) {
    if (!card) return;

    std::array<Card*, 3>* listToCheck = nullptr;
    if (et == entityType::PLAYER) {
        listToCheck = &playerActiveCards;
    } else if (et == entityType::ENEMY) {
        listToCheck = &enemyActiveCards;
    } else if (et == entityType::ENEMY_PRE_PLACE) {
        listToCheck = &enemyPreCards;
    }
    if (!listToCheck) return;

    for (auto& c : *listToCheck) {
        if (c == card) {
            if (card->health <= 0) {
                Deck* deck = (et == entityType::PLAYER) ? playerDeck : enemyDeck;
                if (deck) {
                    deck->discardCard(card);
                }
            }
            c = nullptr;
            break;
        }
    }
}

void Board::printBoard(const std::array<Card*, 3>& board) {
    for (const auto& c : board) {
        std::cout << formatCard(c) << " ";
    }
    std::cout << "\n";
}

void Board::printHand(const std::vector<Card*>& hand) {
    for (size_t i = 0; i < hand.size(); ++i) {
        std::cout << (i + 1) << ") " << formatCard(hand[i]) << " " << '\n';
    }
    std::cout << "\n";
}

void Board::printFullBoard() {
    if (enemy) {
        std::cout << "Enemy HP: " << enemy->health << "\n";
    }

    if (player) {
        std::cout << "Player HP: " << player->health << "\n";
    }

    std::cout << "Enemy Pre:  ";
    printBoard(enemyPreCards);
    std::cout << "Enemy Row:  ";
    printBoard(enemyActiveCards);
    std::cout << "Player Row: ";
    printBoard(playerActiveCards);
    std::cout << "                       " << "\n";
}

Card* Board::getCardAt(entityType et, int lane) {
    if (lane < 0 || lane >= 3) return nullptr;

    if (et == entityType::PLAYER) {
        return playerActiveCards[lane];
    } else if (et == entityType::ENEMY) {
        return enemyActiveCards[lane];
    }
    return nullptr;
}

void Board::damagePlayer(int damage, bool toEnemy) {
    if (damage <= 0) return;
    if (toEnemy) {
        if (enemy) {
            enemy->health -= damage;
            if (player) player->health += damage;
        }
    } else {
        if (player) {
            player->health -= damage;
            if (enemy) enemy->health += damage;
        }
    }
}

void Board::resolveCombat(entityType attackingSide) {
    bool playerAttacking = (attackingSide == entityType::PLAYER);

    for (int lane = 0; lane < 3; lane++) {
        Card* attackerCard = nullptr;

        if (playerAttacking) {
            attackerCard = playerActiveCards[lane];
        } else {
            attackerCard = enemyActiveCards[lane];
        }

        if (!attackerCard) {
            continue;
        }

        CombatContext ctx = resolveTargeting(attackerCard, lane, playerAttacking);
        ctx.board = this;
        ctx.deck = playerAttacking ? playerDeck : enemyDeck;
        ctx.attackerLane = lane;
        ctx.attackerIsPlayer = playerAttacking;

        resolveAttack(ctx);
    }
}

CombatContext Board::resolveTargeting(Card* attacker, int lane, bool attackerIsPlayer) {
    CombatContext ctx;
    ctx.attacker = attacker;
    ctx.blockers.clear();
    ctx.board = this;

    int opposingLane = lane;
    entityType opposingSide = attackerIsPlayer ? entityType::ENEMY : entityType::PLAYER;
    Card* opposingCard = getCardAt(opposingSide, opposingLane);

    if (!opposingCard) {
        return ctx;
    }

    for (SigilName sigilName : attacker->sigils) {
        Sigil* sigil = SigilRegister::instance().getSigil(sigilName);
        if (sigil && !sigil->canBeBlockedBy(opposingCard)) {
            return ctx;
        }
    }

    for (SigilName sigilName : opposingCard->sigils) {
        Sigil* sigil = SigilRegister::instance().getSigil(sigilName);
        if (sigil && !sigil->canBlock(attacker)) {
            return ctx;
        }
    }

    ctx.blockers.push_back(opposingCard);
    return ctx;
}

void Board::resolveAttack(CombatContext& ctx) {
    if (!ctx.attacker) return;

    for (SigilName sigilName : ctx.attacker->sigils) {
        Sigil* sigil = SigilRegister::instance().getSigil(sigilName);
        if (sigil) {
            sigil->onAttack(ctx);
        }
    }

    if (ctx.blockers.empty()) {
        damagePlayer(ctx.attacker->damage, !ctx.attackerIsPlayer);
    } else {
        for (Card* blocker : ctx.blockers) {
            if (blocker) {
                blocker->health -= ctx.attacker->damage;

                if (blocker->health <= 0) {
                    entityType blockerSide = ctx.attackerIsPlayer ? entityType::ENEMY : entityType::PLAYER;
                    removeCard(blockerSide, blocker);
                }

                for (SigilName sigilName : blocker->sigils) {
                    Sigil* sigil = SigilRegister::instance().getSigil(sigilName);
                    if (sigil) {
                        sigil->onBlock(ctx);
                    }
                }
            }
        }
    }
}

void Board::onTurnEnd() {
    currentTurn++;

    for (int lane = 0; lane < 3; lane++) {
        if (playerActiveCards[lane]) {
            for (SigilName sigilName : playerActiveCards[lane]->sigils) {
                Sigil* sigil = SigilRegister::instance().getSigil(sigilName);
                if (sigil) {
                    CombatContext ctx;
                    ctx.attacker = playerActiveCards[lane];
                    ctx.board = this;
                    ctx.deck = playerDeck;
                    ctx.attackerLane = lane;
                    ctx.attackerIsPlayer = true;
                    sigil->onTurnEnd(ctx);
                }
            }
        }

        if (enemyActiveCards[lane]) {
            for (SigilName sigilName : enemyActiveCards[lane]->sigils) {
                Sigil* sigil = SigilRegister::instance().getSigil(sigilName);
                if (sigil) {
                    CombatContext ctx;
                    ctx.attacker = enemyActiveCards[lane];
                    ctx.board = this;
                    ctx.deck = enemyDeck;
                    ctx.attackerLane = lane;
                    ctx.attackerIsPlayer = false;
                    sigil->onTurnEnd(ctx);
                }
            }
        }
    }
}
