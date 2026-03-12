#include "board.h"
#include "../entities/player.h"
#include "../entities/enemy.h"
#include "../sigil/sigil.h"
#include "../deck/deck.h"

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

    std::array<Card*, 3>* listToCheck;

    if (et == entityType::PLAYER) {
        listToCheck = &playerActiveCards;
    } else if (et == entityType::ENEMY) {
        listToCheck = &enemyActiveCards;
    } else if (et == entityType::ENEMY_PRE_PLACE) {
        listToCheck = &enemyPreCards;
    }

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
    for (const auto& i : board) {
        if (!i) {
            std::cout << "[empty] ";
        } else {
            std::cout << "[" << i->name << "] ";
        }
    }
    std::cout << std::endl;
}

void Board::printHand(const std::vector<Card*>& hand) {
    for (const auto& i : hand) {
        if (!i) {
            std::cout << "[empty] ";
        } else {
            std::cout << "[" << i->name << "] ";
        }
    }
    std::cout << std::endl;
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
    if (toEnemy) {
        if (enemy) {
            enemy->health -= damage;
        }
    } else {
        if (player) {
            player->health -= damage;
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
