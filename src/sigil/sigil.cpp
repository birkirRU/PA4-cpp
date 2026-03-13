#include "sigil.h"
#include "../card/card.h"
#include "../board/board.h"

bool AirborneSigil::canBeBlockedBy(const Card* blocker, int currentTurn) const {
    if (currentTurn != 0) {
        return true;
    }
    if (!blocker) {
        return true;
    }
    for (SigilName s : blocker->sigils) {
        if (s == SigilName::MIGHTY_LEAP) {
            return true;
        }
    }
    return false;
}

bool MightyLeapSigil::canBlock(const Card* attacker, int currentTurn) const {
    if (currentTurn != 0) {
        return true;
    }
    if (!attacker) {
        return true;
    }
    for (SigilName s : attacker->sigils) {
        if (s == SigilName::AIRBORNE) {
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

void FledglingSigil::onTurnEnd(CombatContext& ctx) {
    if (!ctx.attacker) {
        return;
    }

    if (ctx.attacker->isBase) {
        ctx.attacker->name = "Wolf";
        ctx.attacker->health = 3;
        ctx.attacker->damage = 2;
        ctx.attacker->bloodCost = 2;
        ctx.attacker->sigils = {SigilName::MIGHTY_LEAP};
        ctx.attacker->isBase = false;
    } else {
        ctx.attacker->damage += 1;
        ctx.attacker->health += 2;
        ctx.attacker->sigils.clear();
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
