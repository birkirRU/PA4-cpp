#ifndef SIGIL_SIGIL_H_
#define SIGIL_SIGIL_H_

#include <string>
#include <memory>
#include <vector>
#include <array>

enum class SigilName {
    WATERBORNE,
    MIGHTY_LEAP,
    FLEDGING,
    AIRBORNE,
    WOLF,
    RAVEN,
    BULLFROG,
    GREAT_WHITE,
    SQUIRREL,
    WOLF_CUP
};

class Card;
class Board;
class Deck;

struct CombatContext {
    Card* attacker;
    std::vector<Card*> blockers;
    Board* board;
    Deck* deck;
    int attackerLane;
    bool attackerIsPlayer;
};

class Sigil {
public:
    virtual ~Sigil() = default;

    virtual void onAttack(CombatContext&) {}
    virtual void onBlock(CombatContext&) {}
    virtual void onTurnEnd(CombatContext&) {}

    virtual bool canBeBlockedBy(const Card*, int) const {
        return true;
    }
    virtual bool canBlock(const Card*, int) const {
        return true;
    }
};

class AirborneSigil : public Sigil {
public:
    bool canBeBlockedBy(const Card* blocker, int currentTurn) const override;
};

class MightyLeapSigil : public Sigil {
public:
    bool canBlock(const Card* attacker, int currentTurn) const override;
};

class WaterborneSigil : public Sigil {
public:
    bool canBlock(const Card*, int currentTurn) const override;
};

class FledglingSigil : public Sigil {
public:
    void onTurnEnd(CombatContext&) override;
};

class SigilRegister {
public:
    SigilRegister();
    static SigilRegister& instance();

    Sigil* getSigil(SigilName name) const;

private:
    std::array<std::unique_ptr<Sigil>, 4> sigils;
};

#endif
