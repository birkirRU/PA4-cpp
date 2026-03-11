#ifndef SIGIL_SIGIL_H_
#define SIGIL_SIGIL_H_

#include <string>
#include <functional>
#include <array>

enum struct Trigger {
    onATTACK,
    onBLOCK,
    onPASSIVE,
    onTURNEND
};

enum struct SigilName {
    WATERBORNE,
    MIGHTY_LEAP,
    FLEDGING,
    AIRBORNE
};


struct SigilDef {
    SigilName name;
    Trigger trigger;
    std::function<void()> effect;
};

class SigilRegister {
    private:
        // SigilName is the key
        std::array<SigilDef, 5> sigilmap = {};
        SigilDef* getMap();

    public:
        void addToMap(const SigilDef sigil);
        void registerSigil(const SigilName& name, Trigger trigger, std::function<void()> effect);
        void initializeSigils();
};
#endif // SIGIL_SIGIL_H_
