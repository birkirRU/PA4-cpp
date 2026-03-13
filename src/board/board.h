#ifndef BOARD_BOARD_H_
#define BOARD_BOARD_H_

#include <array>
#include <iostream>
#include <memory>
#include <vector>
#include "../entities/entity.h"
#include "../sigil/sigil.h"

class Card;
class Player;
class Enemy;
class Deck;

class Board {
public:
    std::array<Card*, 3> enemyActiveCards;
    std::array<Card*, 3> enemyPreCards;
    std::array<Card*, 3> playerActiveCards;

    Player* player;
    Enemy* enemy;
    Deck* playerDeck;
    Deck* enemyDeck;
    int currentTurn;

    Board();

    void placeCard(entityType et, Card* card, int pos);
    void removeCard(entityType et, Card* card);
    void printBoard(const std::array<Card*, 3>& board);
    void printHand(const std::vector<Card*>& hand);
    void printFullBoard();

    void moveEnemyPreCardsToActive();

    void resolveCombat(entityType attackingSide);
    CombatContext resolveTargeting(Card* attacker, int lane, bool attackerIsPlayer);
    void resolveAttack(CombatContext& ctx);

    void onTurnEnd();

    Card* getCardAt(entityType et, int lane);
    void damagePlayer(int damage, bool toEnemy);
};

#endif
