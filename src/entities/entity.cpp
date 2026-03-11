#include "entity.h"


int Entity::_nextId() {
    static int idCounter = 1;
    return idCounter++;
}


