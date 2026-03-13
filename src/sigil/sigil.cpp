#include "sigil.h"
#include "../card/card.h"
#include "../board/board.h"

bool AirborneSigil::canBeBlockedBy(const Card* blocker, int currentTurn) const {
    if (currentTurn != 0) {
        return true;
    }
    for (SigilName sn : blocker->sigils) {
        if (sn == SigilName::MIGHTY_LEAP) {
            return true;
        }
    }
    return false;
}

bool MightyLeapSigil::canBlock(const Card* attacker, int currentTurn) const {
    if (currentTurn != 0) {
        return true;
    }
    for (SigilName sn : attacker->sigils) {
        if (sn == SigilName::AIRBORNE) {
            return true;
        }
    }
    return true;
}

bool WaterborneSigil::canBlock(const Card*, int currentTurn) const {
    if (currentTurn != 0) {
        return true;
    }
    return false;
}

void FledglingSigil::onTurnEnd(CombatContext& context) {
    if (context.attacker->isBase) {
        context.attacker->name = "Wolf";
        context.attacker->health = 3;
        context.attacker->damage = 2;
        context.attacker->bloodCost = 2;
        context.attacker->sigils = {SigilName::MIGHTY_LEAP};
        context.attacker->isBase = false;
    } else {
        context.attacker->damage += 1;
        context.attacker->health += 2;
        context.attacker->sigils.clear();
    }
}

SigilRegister::SigilRegister() {
    sigils[static_cast<size_t>(SigilName::AIRBORNE)] = std::make_unique<AirborneSigil>();
    sigils[static_cast<size_t>(SigilName::MIGHTY_LEAP)] = std::make_unique<MightyLeapSigil>();
    sigils[static_cast<size_t>(SigilName::WATERBORNE)] = std::make_unique<WaterborneSigil>();
    sigils[static_cast<size_t>(SigilName::FLEDGING)] = std::make_unique<FledglingSigil>();
}

SigilRegister& SigilRegister::instance() {
    static SigilRegister instance;
    return instance;
}

Sigil* SigilRegister::getSigil(SigilName name) const {
    size_t idx = static_cast<size_t>(name);
    if (idx < sigils.size()) {
        return sigils[idx].get();
    }
    return nullptr;
}
