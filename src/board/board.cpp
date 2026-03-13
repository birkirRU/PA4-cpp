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
    if (sigils.empty()) {
        return "-";
    }

    std::string out;
    for (size_t i = 0; i < sigils.size(); ++i) {
        if (i > 0) {
            out += ",";
        }
        out += sigilToShort(sigils[i]);
    }
    return out;
}

static std::string formatCard(const Card* c) {
    if (!c || c->health <= 0) {
        return "[empty]";
    }
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
    if (et == entityType::PLAYER) {
        playerActiveCards[pos] = card;
    } else if (et == entityType::ENEMY) {
        enemyActiveCards[pos] = card;
    } else if (et == entityType::ENEMY_PRE_PLACE) {
        enemyPreCards[pos] = card;
    }
}

void Board::removeCard(entityType et, Card* card) {
    std::array<Card*, 3>* arr = nullptr;
    if (et == entityType::PLAYER) {
        arr = &playerActiveCards;
    } else if (et == entityType::ENEMY) {
        arr = &enemyActiveCards;
    } else if (et == entityType::ENEMY_PRE_PLACE) {
        arr = &enemyPreCards;
    }

    for (auto& c : *arr) {
        if (c == card) {
            if (card->health <= 0) {
                Deck* deck = nullptr;
                if (et == entityType::PLAYER) {
                    deck = playerDeck;
                } else {
                    deck = enemyDeck;
                }
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

void Board::moveEnemyPreCardsToActive() {
    int index = 0;
    for (Card* i : enemyPreCards) {
        if (i && !enemyActiveCards[index]) {
            enemyActiveCards[index] = i;
            enemyPreCards[index] = nullptr;
        }
        index++;
    }
}

void Board::printHand(const std::vector<Card*>& hand) {
    for (size_t i = 0; i < hand.size(); ++i) {
        std::cout << (i + 1) << ") " << formatCard(hand[i]) << "\n";
    }
    std::cout << "\n";
}

void Board::printFullBoard() {
    std::cout << "Enemy HP: " << enemy->health << "\n";
    std::cout << "Player HP: " << player->health << "\n";
    std::cout << "Enemy Pre:  ";
    printBoard(enemyPreCards);
    std::cout << "Enemy Row:  ";
    printBoard(enemyActiveCards);
    std::cout << "Player Row: ";
    printBoard(playerActiveCards);
    std::cout << "                       " << "\n";
}

Card* Board::getCardAt(entityType et, int lane) {
    if (lane < 0 || lane >= 3) {
        return nullptr;
    }

    if (et == entityType::PLAYER) {
        return playerActiveCards[lane];
    } else if (et == entityType::ENEMY) {
        return enemyActiveCards[lane];
    }
    return nullptr;
}

void Board::damagePlayer(int damage, bool toEnemy) {
    if (damage <= 0) {
        return;
    }
    if (toEnemy) {
        if (enemy && player) {
            int transfer = damage;
            if (transfer > enemy->health) {
                transfer = enemy->health;
            }
            enemy->health -= transfer;
            player->health += transfer;
            if (player->health > player->maxHealth) {
                player->health = player->maxHealth;
            }
        }
    } else {
        if (player && enemy) {
            int transfer = damage;
            if (transfer > player->health) {
                transfer = player->health;
            }
            player->health -= transfer;
            enemy->health += transfer;
            if (enemy->health > enemy->maxHealth) {
                enemy->health = enemy->maxHealth;
            }
        }
    }
}

static std::array<Card*, 3>& attackerRow(Board* b, bool playerAttacking) {
    if (playerAttacking) {
        return b->playerActiveCards;
    } else {
        return b->enemyActiveCards;
    }
}

static void runSigils(Card* card, void (Sigil::*method)(CombatContext&), CombatContext& context) {
    for (SigilName sn : card->sigils) {
        Sigil* sig = SigilRegister::instance().getSigil(sn);
        if (sig) {
            (sig->*method)(context);
        }
    }
}

static void attackToFace(Board* board, CombatContext& context, int damage) {
    if (damage <= 0) {
        return;
    }
    const char* side;
    if (context.attackerIsPlayer) {
        side = "Player";
    } else {
        side = "Enemy";
    }
    std::cout << side << " " << context.attacker->name << " took " << damage << " off the scale and put it on his (no blocker).\n";
    board->damagePlayer(damage, context.attackerIsPlayer);
}

static void attackBlocker(Board* board, CombatContext& context, Card* blocker, int damage) {
    if (damage <= 0) {
        return;
    }
    const char* side;
    if (context.attackerIsPlayer) {
        side = "Player";
    } else {
        side = "Enemy";
    }
    int hpBefore = blocker->health;
    blocker->health -= damage;

    std::cout << side << " " << context.attacker->name << " (" << damage << " dmg) hit " << blocker->name;
    if (blocker->health <= 0) {
        std::cout << ", " << blocker->name << " killed.";
        int overflow = damage - hpBefore;
        if (overflow > 0) {
            std::cout << " Took " << overflow << " off the scale and put it on his.";
            board->damagePlayer(overflow, context.attackerIsPlayer);
        }
        std::cout << "\n";
        entityType blockerSide;
        if (context.attackerIsPlayer) {
            blockerSide = entityType::ENEMY;
        } else {
            blockerSide = entityType::PLAYER;
        }
        board->removeCard(blockerSide, blocker);
    } else {
        std::cout << ", " << blocker->name << " has " << blocker->health << " hp left.\n";
    }
    runSigils(blocker, &Sigil::onBlock, context);
}

CombatContext Board::resolveTargeting(Card* attacker, int lane, bool attackerIsPlayer) {
    CombatContext context;
    context.attacker = attacker;
    context.blockers.clear();
    context.board = this;

    entityType opposingSide;
    if (attackerIsPlayer) {
        opposingSide = entityType::ENEMY;
    } else {
        opposingSide = entityType::PLAYER;
    }
    Card* opposing = getCardAt(opposingSide, lane);
    if (!opposing) {
        return context;
    }

    for (SigilName sn : attacker->sigils) {
        Sigil* sig = SigilRegister::instance().getSigil(sn);
        if (sig && !sig->canBeBlockedBy(opposing, currentTurn)) {
            return context;
        }
    }
    for (SigilName sn : opposing->sigils) {
        Sigil* sig = SigilRegister::instance().getSigil(sn);
        if (sig && !sig->canBlock(attacker, currentTurn)) {
            return context;
        }
    }
    context.blockers.push_back(opposing);
    return context;
}

void Board::resolveAttack(CombatContext& context) {
    runSigils(context.attacker, &Sigil::onAttack, context);
    int damage = context.attacker->damage;
    if (context.blockers.empty()) {
        attackToFace(this, context, damage);
    } else {
        for (Card* blocker : context.blockers) {
            attackBlocker(this, context, blocker, damage);
        }
    }
}

void Board::resolveCombat(entityType attackingSide) {
    bool playerAttacking = (attackingSide == entityType::PLAYER);
    std::array<Card*, 3>& row = attackerRow(this, playerAttacking);

    for (int lane = 0; lane < 3; lane++) {
        Card* attacker = row[lane];
        if (!attacker) {
            continue;
        }
        CombatContext context = resolveTargeting(attacker, lane, playerAttacking);
        context.board = this;
        if (playerAttacking) {
            context.deck = playerDeck;
        } else {
            context.deck = enemyDeck;
        }
        context.attackerLane = lane;
        context.attackerIsPlayer = playerAttacking;
        resolveAttack(context);
    }
}

void Board::onTurnEnd() {
    currentTurn++;

    for (int lane = 0; lane < 3; lane++) {
        if (playerActiveCards[lane]) {
            for (SigilName sigilName : playerActiveCards[lane]->sigils) {
                Sigil* sigil = SigilRegister::instance().getSigil(sigilName);
                if (sigil) {
                    CombatContext context;
                    context.attacker = playerActiveCards[lane];
                    context.board = this;
                    context.deck = playerDeck;
                    context.attackerLane = lane;
                    context.attackerIsPlayer = true;
                    sigil->onTurnEnd(context);
                }
            }
        }

        if (enemyActiveCards[lane]) {
            for (SigilName sigilName : enemyActiveCards[lane]->sigils) {
                Sigil* sigil = SigilRegister::instance().getSigil(sigilName);
                if (sigil) {
                    CombatContext context;
                    context.attacker = enemyActiveCards[lane];
                    context.board = this;
                    context.deck = enemyDeck;
                    context.attackerLane = lane;
                    context.attackerIsPlayer = false;
                    sigil->onTurnEnd(context);
                }
            }
        }
    }
}
