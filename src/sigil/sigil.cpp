#include "sigil.h"
#include "../card/card.h"
#include "../board/board.h"

bool AirborneSigil::canBeBlockedBy(const Card* blocker) const {
    if (!blocker) return true;
    for (SigilName s : blocker->sigils) {
        if (s == SigilName::MIGHTY_LEAP) {
            return true;
        }
    }
    return false;
}

bool MightyLeapSigil::canBlock(const Card* attacker) const {
    if (!attacker) return true;
    for (SigilName s : attacker->sigils) {
        if (s == SigilName::AIRBORNE) {
            return true;
        }
    }
    return true;
}

WaterborneSigil::WaterborneSigil() : turnCounter(0) {}

bool WaterborneSigil::canBeBlockedBy(const Card* /* blocker */) const {
    return (turnCounter % 2 == 1);
}

void WaterborneSigil::onTurnEnd(CombatContext&) {
    turnCounter++;
}

void FledglingSigil::onTurnEnd(CombatContext& ctx) {
    if (!ctx.attacker) return;

    if (ctx.attacker->isBase) {
        ctx.attacker->damage += 2;
        ctx.attacker->health += 1;
        ctx.attacker->sigils = {SigilName::MIGHTY_LEAP};
    } else {
        ctx.attacker->damage += 1;
        ctx.attacker->health += 2;
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
