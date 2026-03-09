#include "sigil.h"


SigilDef* SigilRegister::getMap() {
    return sigilmap.data();
}

void SigilRegister::addToMap(const SigilDef sigil) {
    getMap()[static_cast<size_t>(sigil.name)] = sigil;
}

void SigilRegister::registerSigil(const SigilName& name, Trigger trigger, std::function<void()> effect) {
    SigilDef sigil;
    sigil.name = name;
    sigil.trigger = trigger;
    sigil.effect = effect;
    SigilRegister::addToMap(sigil);
}


void SigilRegister::initializeSigils() {
    registerSigil(
        SigilName::WATERBORNE,
        Trigger::onPASSIVE,
        []() {
        }
    );

    registerSigil(
        SigilName::MIGHTY_LEAP,
        Trigger::onBLOCK,
        []() {
        }
    );

    registerSigil(
        SigilName::FLEDGING,
        Trigger::onPASSIVE,
        []() {
        }
    );

    registerSigil(
        SigilName::AIRBORNE,
        Trigger::onATTACK,
        []() {
        }
    );
}
