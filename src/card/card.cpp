#include "card.h"

Card::Card(const std::string& name, int health, int damage, int bloodCost,
           const std::vector<SigilName>& sigils, bool isBase)
    : name(name), health(health), damage(damage), bloodCost(bloodCost),
      sigils(sigils), isBase(isBase) {}
